from tkinter import *
from tkinter import ttk
from googletrans import Translator,LANGUAGES
import csv
arrData=[]
def write_list_to_csv(data, filename='translateLang1.csv'):
    with open(filename, 'a', newline='',encoding='utf-8') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(data)
        
def read_from_csv(filename='translateLang1.csv'):
    with open(filename, 'r', encoding='utf-8') as csvfile:
        csv_reader = csv.reader(csvfile)
        for row in csv_reader:
            print(row[0],"\t",row[1])
            
def convert(text="type",src="English",dest="Hindi"):
    text1=text
    src1=src
    dest1=dest
    trans=Translator()
    trans1=trans.translate(text,src=src1,dest=dest1)
    return trans1.text

def myData():
    arrData=[]
    s=comb_sor.get()
    d=comb_dest.get()
    msg1=Sor_txt.get(1.0,END)
    m1=msg1[:-1]
    msg2=convert(text=msg1, src=s, dest=d)
    arrData.append(m1)
    arrData.append(msg2)
    #print(arrData)
    write_list_to_csv(arrData)
    read_from_csv()
    dest_txt.delete(1.0,END)
    dest_txt.insert(END,msg2)
      
 

root=Tk()
root.title("Translator ")
root.geometry("500x700")
root.config(bg='black')
lab_txt=Label(root,text="Language Translator",font=("Time New Roman",30,"bold"),bg='black')
lab_txt.place(x=30,y=50,height=45,width=500)

lab_txt=Label(root,text="Source Text",font=("Time New Roman",20,"bold"),bg='black')
lab_txt.place(x=100,y=100,height=20,width=300)

frame=Frame(root).pack(side=BOTTOM)
Sor_txt=Text(frame,font=("Time New Roman",20,"bold"),wrap=WORD, fg="white")
Sor_txt.place(x=10,y=130,height=150,width=480)

list_text=list(LANGUAGES.values())
comb_sor=ttk.Combobox(frame,value=list_text, font=("Time New Roman",13,"bold"))
comb_sor.place(x=10,y=300, height=40, width=150)
comb_sor.set("English")

button_change=Button(frame,text="TRANSLATE",relief=RAISED,command=myData,font=("Time New Roman",13,"bold"))
button_change.place(x=170,y=300, height=40, width=150)

comb_dest=ttk.Combobox(frame,value=list_text,font=("Time New Roman",13,"bold"))
comb_dest.place(x=330,y=300, height=40, width=150)
comb_dest.set("English")

lab_txt=Label(root,text="Destination Text",font=("Time New Roman",20,"bold"),bg='black')
lab_txt.place(x=100,y=360,height=20,width=300)

dest_txt=Text(frame,font=("Time New Roman",20,"bold"),wrap=WORD, fg="white")
dest_txt.place(x=10,y=400,height=150,width=480)

root.mainloop()
