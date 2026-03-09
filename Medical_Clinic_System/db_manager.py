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
        
    def disconnect(self):
        try:
            if self.con is not None:
                self.con.close()
        except mysql.connector.Error:
            self.error = "Nu se poate inchide conexiunea la baza de date!"
            raise Exception(self.error)
        
    def adaugamedici(self, Nume, Prenume,Specializare,Program_medic):
        if self.con is not None:
            try: 
                cursor = self.con.cursor() 
                query = "insert into doctori(Nume, Prenume,Specializare,Program_medic) values(%s,%s,%s,%s)"
                values = values(Nume, Prenume,Specializare,Program_medic)
                cursor.execute(query,values)
                self.con.commit()
                print("Datele au fost inserate !")
                cursor.close()
            except mysql.connector.Error as er:
                self.error = "ExceptieSQL: Reactualizare nereusita; este posibil sa existe duplicate sau erori de sintaxa."
                raise Exception(self.error)
        else:
            self.error = "Conexiunea cu baza de date a fost pierduta!"
            raise Exception(self.error)
    def adaugapacienti(self, Nume, Prenume,Boli_cronice):
        if self.con is not None:
            try:
                cursor = self.con.cursor()
                query = "insert into pacienti(Nume, Prenume,Boli_cronice) values (%s,%s,%s)"
                cursor.execute(query,(Nume, Prenume,Boli_cronice))
                self.con.commit()
                print("Date inserate")
            except mysql.connector.Error as er:
                self.error = "ExceptieSQL: Reactualizare nereusita; este posibil sa existe duplicate sau erori de sintaxa."
                raise Exception(self.error)
        else:
            self.error = "Conexiunea cu baza de date a fost pierduta!"
            raise Exception(self.error)
    
    def adaugaprogramari(self, iddoctor, idpacient, DataProgramare,Ora_Programare,Motiv):
        if self.con is not None:
            try:
                cursor =  self.con.cursor()
                query= "insert into clasa(iddoctor, idpacient, DataProgramare,Ora_Programare,Motiv) values (%s,%s,%s,%s,%s)";
                cursor.execute(query,(iddoctor, idpacient, DataProgramare,Ora_Programare,Motiv))
                self.con.commit()
                print("Datele au fost adaugate")
                cursor.close()
            except mysql.connector.Error as er:
                self.error = "ExceptieSQL: Reactualizare nereusita; este posibil sa existe duplicate sau erori de sintaxa."
                raise Exception(self.error)
        else:
            self.error = "Conexiunea cu baza de date a fost pierduta!"
            raise Exception(self.error)
        
    def vedeTabela(self,tabel):
        a = None
        try:
            cursor = self.con.cursor()
            query = f"select * from `clinic`.`{tabel}`"
            cursor.execute(query)
            a = cursor.fetchall()
            print("Afisarea a fost facuta")
            cursor.close()
            return a
        except  mysql.connector.Error as inter_err:
            self.error = f"Eroarea: {inter_err.errno}: {inter_err.msg};"
            raise Exception(self.error)
        except Exception:
            self.error = "A aparut o exceptie in timp ce se extrageau datele."
            raise Exception(self.error)
    def vedeprogramari(self):
        a = None
        try:
            query = f"select d.iddoctor, d.Nume, d.Prenume, d.Specializare, d.Program_medic, p.idpacient, p.Nume, p.Prenume, p.Boli_cronice, v.idprogramare, v.DataProgramare, v.Ora_programare, v.Motiv, v.status_programare from doctori d, pacienti p , programari v where d.iddoctor = v.iddoctor and p.idpacient = v.idpacient"
            cursor = self.con.cursor()
            cursor.execute(query)
            a = cursor.fetchall()
            print("Afioare tabela programare cu succes")
            cursor.close()
            return a
        except mysql.connector.Error as inter_err:
            self.error = f"Eroarea: {inter_err.errno}: {inter_err.msg};"
            raise Exception(self.error)
        except Exception:
            self.error = "A aparut o exceptie in timp ce se extrageau datele."
            raise Exception(self.error)
    def stergeDateTabela(self, primaryKeys, tabela, dupaID):
        if self.con is not None:
            try: 
                cursor = self.con.cursor()
                delete = f"delete from {tabela} where {dupaID} = %s;"
                for i in primaryKeys:
                    aux = int(i)
                    cursor.execute(delete, (aux,))
                self.con.commit()
                cursor.close()
                print(f"S-au sters {len(primaryKeys)} inregistrari")
            except mysql.connector.Error as sqle:
                self.error = f"ExceptieSQL ({sqle.errno}): Reactualizare nereusita; {sqle.msg}"
                self.con.rollback()
                raise Exception(self.error)
            except Exception as e:
                self.error = f"A aparut o exceptie in timp ce erau sterse inregistrarile: {e}"
                raise Exception(self.error)
        else:
            self.error = "Exceptie: Conexiunea cu baza de date a fost pierduta."
            raise Exception(self.error)
    def stergeTabela(self,tabela):
        if self.con is not None:
            try:
                cursor = self.con.cursor()
                query = f"delete from {tabela};"
                cursor.execute(query)
                self.con.commit()
                cursor.close()
            except mysql.connector.Error as errors:
                self.error = f"Stergere nereusita! A aparut eroarea:{errors.errno}"
                raise Exception(self.error)
        else:
            self.error = "Exceptie: Conexiunea cu baza de date a fost pierduta."
            raise Exception(self.error)
    def modificaTabela(self, tabela,IDTabela,ID,campuri,valori):
        if self.con is not None:
            try:
                set_parts = [f"`{campuri[i]}` = %s" for i in range(len(campuri))]
                query = f"UPDATE `{tabela}` SET {', '.join(set_parts)} WHERE `{IDTabela}` = %s"
                valori_update = list(valori) + [ID]
                cursor = self.con.cursor()
                cursor.execute(query, valori_update)
                self.con.commit()
                cursor.close()
                print("Update realizat cu succes!")
            except mysql.connector.Error as errors:
                self.error = f"Modificare nereusita! A aparut eroarea:{errors.errno}"
                raise Exception(self.error)
        else:
            self.error = "Exceptie: Conexiunea cu baza de date a fost pierduta."
            raise Exception(self.error)
    def intoarceLinie(self,tabela,ID):
        rs = None
        try:
            query = f"Select * from `{tabela}` where idprofesor='{ID}';"
            cursor = self.con.cursor(buffered=True)
            cursor.execute(query)
            rs = cursor.fetchall()
            cursor.close()
            return rs
        except mysql.connector.Error as errors:
                self.error = f"Interogare nereusita! A aparut eroarea:{errors.errno}"
                raise Exception(self.error)
        except Exception:
            self.error = f"Exceptie: {Exception}"
            raise Exception(self.error)
        
    def intoarcereliniedupaID(self,tabela,denumireID,ID):
        rs = None
        try:
            query = f"Select * from `{tabela}` where `{denumireID}` = %s;"
            cursor = self.con.cursor(buffered=True)
            cursor.execute(query,(ID,))
            rs = cursor.fetchall()
            cursor.close()
            return rs
        except mysql.connector.Error as errors:
                self.error = f"Interogare nereusita! A aparut eroarea:{errors.errno}"
                raise Exception(self.error)
        except Exception:
            self.error = f"Exceptie: {Exception}"
            raise Exception(self.error)    

    def intoarceProgramare(self,ID):
        a = None
        try:
            query = f"select d.iddoctor, d.Nume, d.Prenume, d.Specializare, d.Program_medic, p.idpacient, p.Nume, p.Prenume, p.Boli_cronice, v.idprogramare, v.DataProgramare, v.Ora_programare, v.Motiv, v.status_programare from doctori d, pacienti p , programari v where d.iddoctor = v.iddoctor and p.idpacient = v.idpacient"
            cursor = self.con.cursor(buffered=True)
            cursor.execute(query,(ID,))
            a = cursor.fetchall()
            cursor.close()
            return a
        except mysql.connector.Error as errors:
                self.error = f"Interogare nereusita! A aparut eroarea:{errors.errno}"
                raise Exception(self.error)
        except Exception:
            self.error = f"Exceptie: {Exception}"
            raise Exception(self.error)
    def vede_user(self):
        a = None
        try:
            cursor = self.con.cursor()
            query = 'select user,host from mysql.user;'
            cursor.execute(query)
            a = cursor.fetchall()
            print("Lista cu useri este afisata!")
            return a
        except  mysql.connector.Error as inter_err:
            self.error = f"Eroarea: {inter_err.errno}: {inter_err.msg};"
            raise Exception(self.error)
        except Exception:
            self.error = "A aparut o exceptie in timp ce se extrageau datele."
            raise Exception(self.error) 
    def sterge_user(self, user, host = 'localhost'):
        try:
            cursor = self.con.cursor()
            query = f"drop user `{user}`@`{host}`;"
            cursor.execute(query)
            self.con.commit()
            cursor.close()
            print(f"Userul `{user}`@`{host}` a fost sters!")
        except Exception:
            self.error = f"Exceptie: {Exception}"
            raise Exception(self.error)
        


    



        






