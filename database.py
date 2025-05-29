import sqlite3
import time

def db_init(db_name):
    conn = sqlite3.connect(db_name)

    conn.commit()
    conn.close()

def create_table(db_name, table_name, features):
    conn = sqlite3.connect(db_name)
    c = conn.cursor()
    sql_query = f"create table {table_name} {features}"
    # print(sql_query)
    c.execute(sql_query)
    
    conn.commit()
    conn.close()

def see_all(db_name, table_name):
    conn = sqlite3.connect(db_name)
    c = conn.cursor()
    sql_query = f"select * from {table_name}"
    # print(sql_query)
    c.execute(sql_query)
    print(c.fetchall())
    conn.commit()
    conn.close()

def add_student(db_name, table_name, values):
    conn = sqlite3.connect(db_name)
    c = conn.cursor()
    sql_query = f"insert into {table_name} (id, name, roll_number, grade) values(?,?,?,?)"
    # print(sql_query)
    c.executemany(sql_query, values)
    conn.commit()
    conn.close()

def search_grade(db_name, table_name, name):
    conn = sqlite3.connect(db_name)
    c = conn.cursor()
    sql_query = f"select * from {table_name} where name like '{name}'"
    # print(sql_query)
    c.execute(sql_query)
    print(c.fetchall())
    conn.commit()
    conn.close()

def update_grade(db_name, table_name, roll_no, grade):
    conn = sqlite3.connect(db_name)
    c = conn.cursor()
    sql_query = f"update {table_name} set grade = '{grade}' where roll_number like '{roll_no}'"
    # print(sql_query)
    c.execute(sql_query)
    conn.commit()
    conn.close()

def delete_record(db_name, table_name, roll_no):
    conn = sqlite3.connect(db_name)
    c = conn.cursor()
    sql_query = f"delete from {table_name} where roll_number like '{roll_no}'"
    # print(sql_query)
    c.execute(sql_query)
    conn.commit()
    conn.close()

def order(db_name, table_name, name):
    conn = sqlite3.connect(db_name)
    c = conn.cursor()
    sql_query = f"select * from {table_name} order by name"
    # print(sql_query)
    c.execute(sql_query)
    print(c.fetchall())
    conn.commit()
    conn.close()

# def alter():
#     conn = sqlite3.connect("school.db")
#     c = conn.cursor()
#     sql_query = f"drop table students"
#     # print(sql_query)
#     c.execute(sql_query)
#     print(c.fetchall())
#     conn.commit()
#     conn.close()

