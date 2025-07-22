import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
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

    # Ir buscar o id do usuário
    user_id = session["user_id"]
    # Ver o saldo do usuário acima
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # criar tabela com as transações do usuário
    transactions = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)

    portofolio = [stock for stock in transactions if stock["total_shares"]]

    for stock in portofolio:
        quote = lookup(stock["symbol"])
        stock["price"] = quote["price"]
        stock["total_value"] = stock["total_shares"] * stock["price"]

    total_value = cash + sum(stock["total_value"] for stock in portofolio)

    return render_template("index.html", portofolio=portofolio, cash=cash, total_value=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()

        if not symbol:
            return apology("must provide valid symbol and share number", 400)

        shares = request.form.get("shares")
        # Verificar se o número de ações é válido ou não
        try:
            shares = int(shares)
            if shares <= 0:
                raise ValueError
        except (ValueError, TypeError):
            return apology("must provide valid symbol and share number", 400)

        # Alocar a ação a stock
        stock = lookup(symbol)
        # Verificar se válidp
        if stock is None:
            return apology("Must provide valid symbol", 400)

        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id= ?", user_id)[0]["cash"]

        total_cost = stock["price"]*shares

        if total_cost > user_cash:
            return apology("You don't have enough cash for this purchase", 400)

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?,?,?,?,?)",
            user_id,
            stock["symbol"],
            shares,
            stock["price"],
            "BUY"
        )

        # Atualizar saldo
        db.execute(
            "UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id
        )

        flash(f"Purchase done! {shares} share(s) of {stock['symbol']} for {usd(total_cost)}!")
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id = ? ORDER BY timestamp DESC",
        user_id
    )
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

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
    """Get stock quote."""

    if request.method == "POST":
        # obter o símbolo da ação do formulário
        symbol = request.form.get("symbol")
        if not symbol or symbol is None:
            return apology("must provide stock symbol", 400)

        # Anexar a cotação do simbolo ao usar a lookup já escrito
        stock = lookup(symbol)
        # verificar se o símbolo foi introduzido
        # Ver se existe o simbolode stock
        if stock is None:
            return apology("Simbolo de stock não existe", 400)
        # print(stock)
        # Mostrar a página quoted caso o simbolo existe **Ainda falta fazer a pagina
        return render_template("quoted.html", stock=stock)
    # print(stock)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    # Eliminate last session
    session.clear()

    """Register user, ir buscar os dados introduzidos que foram enviados dos campus html"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Verificar se os campos foram preenchidos
        if not username or not password or not confirmation:
            return apology("Must provide username and password :)", 400)

        # Verificar se as passwords batem, mesmo com todos os campos preenchidos e as passes diferentes não está a vir para este, ver
        if password != confirmation:
            return apology("Passwords do not match)", 400)

        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)",
                username,
                generate_password_hash(password)
            )
        except ValueError:
            return apology("username already exists", 400)

        return redirect("/login")

    return render_template("register.html")
    # print(username)
    # print(password)
    # print(confirmation)

# MUDAR A PALAVR PASSE


@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def change_password():
    # Eliminate last session
    """Register user, ir buscar os dados introduzidos que foram enviados dos campus html"""
    if request.method == "POST":
        old_password = request.form.get("old_password")
        new_password = request.form.get("new_password")
        new_confirmation = request.form.get("new_confirmation")

        # Verificar se os campos foram preenchidos
        if not new_password or not old_password or not new_confirmation:
            return apology("Must provide username and password :)", 400)

        current_pass_hash = db.execute("SELECT hash FROM users WHERE id=?", session["user_id"])
        if not current_pass_hash:
            return apology("Error with Password", 400)

        # Verificar se as passwords batem, mesmo com todos os campos preenchidos e as passes diferentes não está a vir para este, ver
        # Ver como se vai buscar a password antiga
        if not check_password_hash(current_pass_hash[0]["hash"], old_password):
            return apology("That's not your password!", 400)

        if new_password != new_confirmation:
            return apology("Passwords do not match", 400)

        db.execute("UPDATE users SET hash = ? WHERE id = ?",
                   generate_password_hash(new_password),
                   session["user_id"])

        flash("Password Changed Successfully!")

        return redirect("/")

    return render_template("changepassword.html")

# ACABAR O MUDAR PASSOWORD


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
        user_id
    )

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("plz provide symbol", 400)

        shares = request.form.get("shares")  # Vem como string
        try:
            shares = int(shares)
            if shares <= 0:
                raise ValueError
        except (ValueError, TypeError):
            return apology("most provide a valid symbol and share eheh", 400)

        # Alocar a ação a stock
        stock = lookup(symbol)
        # Verificar se válidp
        if stock is None:
            return apology("Must provide valid symbol", 400)

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        # print(user_cash)

        ## VERIFICAR SE TEM AÇÕES SUFICIENTES*****************##

        total_cost = stock["price"]*shares

        new_cash = user_cash + total_cost

        # VErificar se User detem todas as shares
        user_shares = db.execute(
            "SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = ? AND symbol = ?",
            user_id,
            symbol
        )[0]["total_shares"]

        try:
            user_shares = int(user_shares)
            if user_shares is None or shares > user_shares:
                return apology("You don't have that many shares, keep Dreaming", 400)
        except (ValueError, TypeError):
            return apology("Have to buy so you can have it", 400)

        # Adicionar à tabela de transações
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?,?,?,?,?)",
            user_id,
            stock["symbol"],
            -shares,
            stock["price"],
            "SELL"
        )

        # Update de cash do user
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            new_cash,
            user_id
        )

        flash(f"SOLD! {shares} share(s) of {stock['symbol']} for {usd(total_cost)}!")
        return redirect("/")

    return render_template("/sell.html", stocks=stocks)
