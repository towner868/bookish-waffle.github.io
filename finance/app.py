import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Portfolio Build

    portfolio = db.execute(
        "SELECT SUM(shares), stockSymbol, companyName, stockPrice, SUM(totalPrice) FROM portfolio WHERE user_id = ? GROUP BY stockSymbol", session["user_id"])
    name = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    totalAssets = 0
    for i in range(len(portfolio)):
        currentPrice = lookup(portfolio[i]["stockSymbol"])
        portfolio[i]["stockPrice"] = currentPrice["price"]
        portfolio[i]["SUM(totalPrice)"] = (currentPrice["price"] * portfolio[i]["SUM(shares)"])
        totalAssets += portfolio[i]["SUM(totalPrice)"]
        portfolio[i]["stockPrice"] = usd(portfolio[i]["stockPrice"])
        portfolio[i]["SUM(totalPrice)"] = usd(portfolio[i]["SUM(totalPrice)"])

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    if not cash:
        return render_template("login.html")
    grandTotal = cash[0]["cash"] + totalAssets
    cash[0]["cash"] = usd(cash[0]["cash"])
    grandTotal = usd(grandTotal)

    return render_template("index.html", portfolio=portfolio, name=name, cash=cash, total=grandTotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide ticker symbol", 400)
        shares = request.form.get("shares")
        if shares.isdigit() == False:
            return apology("must provide positive, whole number of shares", 400)
        shares = int(shares)
        if (shares * 10) % 10 != 0:
            return apology("must provide positive, whole number of shares", 400)
        if shares < 1:
            return apology("must provide positive, whole number of shares", 400)
        quote = lookup(symbol)
        if quote is None:
            return apology("incorrect symbol", 400)
        sharePrice = quote["price"]
        companyName = quote["name"]
        totalPrice = float(sharePrice * shares)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        purchased = "purchased"
        if totalPrice > cash[0]["cash"]:
            return apology("sorry, insufficent funds", 400)
        newBalance = cash[0]["cash"] - totalPrice
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newBalance, session["user_id"])
        db.execute("INSERT INTO purchases (user_id, shares, companyName, stockSymbol, stockPrice, totalPrice, DateTime, transaction_history) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",
                   session["user_id"], shares, companyName, symbol, sharePrice, totalPrice, datetime.datetime.now(), purchased)
        db.execute("INSERT INTO portfolio (user_id, shares, companyName, stockSymbol, stockPrice, totalPrice, DateTime) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   session["user_id"], shares, companyName, symbol, sharePrice, totalPrice, datetime.datetime.now())
        flash("purchased successfully")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    name = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    purchases = db.execute(
        "SELECT stockSymbol, stockPrice, shares, DateTime, transaction_history FROM purchases WHERE user_id = ?", session["user_id"])
    sales = db.execute(
        "SELECT stockSymbol, stockPrice, shares, DateTime, transaction_history FROM sales WHERE user_id = ?", session["user_id"])
    history = purchases + sales
    history = sorted(history, key=lambda l: l["DateTime"], reverse=False)
    return render_template("history.html", history=history, name=name)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        flash("You have logged in successfully, " + request.form.get("username"))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide ticker symbol", 400)
        quote = lookup(symbol)
        if quote is None:
            return apology("incorrect symbol", 400)
        quote["price"] = usd(quote["price"])
        return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    session.clear()

    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")
    users = db.execute("SELECT * FROM users")

    if request.method == "POST":

        if not username:
            return apology("must provide username", 400)

        elif not password:
            return apology("must provide password", 400)

        elif password != confirmation:
            return apology("must confirm password", 400)

        for row in users:
            if check_password_hash(users[0]["hash"], password):
                return apology("password already taken", 400)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        regRow = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = regRow[0]["id"]
        flash("Your account has been created successfully, " + username)
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    optionSymbols = db.execute("SELECT stockSymbol FROM portfolio WHERE user_id = ? GROUP BY stockSymbol", session["user_id"])
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide ticker symbol", 400)
        shares = int(request.form.get("shares"))
        if shares < 1:
            return apology("must provide number of shares", 400)
        symbol = request.form.get("symbol")
        currentShares = db.execute(
            "SELECT SUM(shares) FROM portfolio WHERE stockSymbol = ? AND user_id = ? GROUP BY stockSymbol", symbol, session["user_id"])
        if currentShares[0]["SUM(shares)"] < shares:
            return apology("sell shares exceeds owned shares", 400)
        quote = lookup(symbol)
        sharePrice = quote["price"]
        companyName = quote["name"]
        totalPrice = float(sharePrice * shares)
        newSharetotal = currentShares[0]["SUM(shares)"] - shares
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        newBalance = cash[0]["cash"] + totalPrice
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newBalance, session["user_id"])
        sold = "sold"
        db.execute("INSERT INTO sales (user_id, shares, companyName, stockSymbol, stockPrice, totalPrice, DateTime, transaction_history) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",
                   session["user_id"], shares, companyName, symbol, sharePrice, totalPrice, datetime.datetime.now(), sold)
        if newSharetotal == 0:
            db.execute("DELETE FROM portfolio WHERE companyName = ?", companyName)
            flash("sold successfully")
            return redirect("/")
        else:
            db.execute("INSERT INTO portfolio (user_id, shares, companyName, stockSymbol, stockPrice, totalPrice, DateTime) VALUES (?, ?, ?, ?, ?, ?, ?)",
                       session["user_id"], shares * -1, companyName, symbol, sharePrice, totalPrice, datetime.datetime.now())
            flash("sold successfully")
        return redirect("/")
    else:
        return render_template("sell.html", optionSymbols=optionSymbols)


@app.route("/updatePass", methods=["GET", "POST"])
@login_required
def updatePass():
    password = request.form.get("password")
    passConfirm = request.form.get("passConfirm")
    newPass = request.form.get("newPass")
    newPassConfirm = request.form.get("newPassConfirm")

    users = db.execute("SELECT * FROM users")

    if request.method == "POST":

        if not password:
            return apology("must provide password", 400)

        elif not passConfirm:
            return apology("must confirm password", 400)

        elif not newPass:
            return apology("must provide new password", 400)

        elif not newPassConfirm:
            return apology("must confirm new password", 400)

        elif password != passConfirm:
            return apology("must confirm password", 400)

        elif newPass != newPassConfirm:
            return apology("must confirm new password", 400)

        for row in users:
            if check_password_hash(users[0]["hash"], newPass):
                return apology("password already taken", 400)

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(newPass), session["user_id"])
        flash("Your new password has been set.")
        return redirect("/")

    else:
        return render_template("updatePass.html")
