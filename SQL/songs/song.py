import sqlite3
import os


connection = sqlite3.connect("songs.db")
cursor = connection.cursor()

sql_folder ="ficheiros_sql"

answers = []

for i in range(1,9):
    sql_file = os.path.join(sql_folder, f"{i}.sql")
    with open ( sql_file, "r") as file:
        query = file.read().strip()


        cursor.execute(query)
        rows = cursor.fetchall()


        if rows:
            result = "\n".join(["\t".join(map(str,row)) for row in rows])
        else:
            result = "NULL"

        answers.append(f"Query {i}:\n{result}")
connection.close()

with open("answers.txt", "w") as file:
    for answer in answers:
        file.write("\n\n".join(answers))

print("Respostas guardadas em 'answers.txt'")



