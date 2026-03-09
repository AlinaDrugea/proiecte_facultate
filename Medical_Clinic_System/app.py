from flask import Flask, render_template, request, session, redirect, url_for
from db_manager import PythonCon
app = Flask(__name__)
app.secret_key = "cheieaplicatie"
db = PythonCon()

@app.route('/')
def index():
    cont_creat = request.args.get('succes')
    cont_eroare = request.args.get('eroare')
    return render_template('index.html', cont_creat= cont_creat, eroare=cont_eroare)

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('index'))

def acces():
    if request.method == 'POST':    
        user = request.form.get("username")
        password = request.form.get("password")
        print(user,password)
        try:
            db.connect(user=user,password=password)
            db.disconnect()
            session['user'] = user
            session['password'] = password
            if user == 'root':
                return render_template('acces_root.html')
            return render_template('dupa_acces.html')
        except Exception as e:
            return redirect(url_for('index',eroare = 1))

    else:
        if 'user' in session and 'password' in session:
            db.connect(user=session['user'],password=session['password'])
            db.disconnect()
            return render_template('dupa_acces.html')
        else:
            return redirect(url_for('index'))    
@app.route('/acces_root')
def root():
    if session.get('user') == 'root':
        return render_template('acces_root.html')
    
@app.route('/afisare_user')
def vede_user():
    if session.get('user') != 'root':
        return render_template('status.html', titlu="Acces Refuzat", mesaj="Nu aveți permisiunea de a vedea utilizatorii sistemului.")
    
    try:
        db.connect(user = session['user'], password=session['password'])
        date = db.vede_user()
        db.disconnect()
        return render_template('afisare_user.html', users = date)
    
    except Exception as er:
        if db.con : db.disconnect()
        return f"Eroare lista: {er}"