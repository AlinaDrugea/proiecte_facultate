import mysql.connector
from mysql.connector import errorcode

class PythonCon:
    def __init__(self):
        self.con = None
        self.error = None

    def connect(self, bd = "clinic", ip ="localhost", user = "root", password = "abcd1234"):
        try:
            self.con = mysql.connector.connect(
               host=ip, 
                port=3306,
                database=bd,
                user = user,
                password = password 
            )
            print(f"Conexiune reusita {bd} {ip}")

        except mysql.connector.Error as err:
             if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
                self.error = "Utilizator sau parola gresita."
             elif err.errno == errorcode.ER_BAD_DB_ERROR:
                self.error = f"Baza de date {bd} nu exista."    
             else:
                self.error = f"SQLException: {err.msg}"
             raise Exception(self.error)
        except Exception as e:
            self.error = f"A aparut o eroare neprevazuta: {e}"
            raise Exception(self.error)

    def create_user(self, user, password):
        try: 
            cursor = self.con.cursor(buffered=True)
            query = "create user %s@'localhost' identified by %s;"
            cursor.execute(query,(user,password))

            query_grant  = "grant create, select, insert, update, delete on clinic.* to %s@'localhost';"
            cursor.execute(query_grant,(user,))
            self.con.commit()
            cursor.close()
        except mysql.connector.Error as er:
            return f"Eroare: {er.msg}"

    def active_account(self, user):
        acc = None
        try:
            cursor = self.con.cursor()
            query = 'select user from mysql.user where usre = %s'
            cursor.execute(query,(user,))
            acc = cursor.fetchall()
            cursor.close()
            return acc
        except mysql.connector.Error as er:
            return f"Eroare: {er.msg}"
        
        





