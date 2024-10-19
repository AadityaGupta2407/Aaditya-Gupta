import pickle

list=[]
def adddetail():
    count = int(input("enter no of students: "))
    for i in range(count):
        name = input("enter name: ")
        phone = int(input("enter phone no: "))
        email = input("enter email id: ")
        list.append([name,phone,email])
    p = open("sample1","wb")
    pickle.dump(list,p)
    p.close()

def finddetail():
    find = input("enter name: ")
    p = open("sample1","rb")
    k = pickle.load(p)
    p.close()
    c=0
    for i in k:
        if i[0] == find:
            c=c+1
            print(i)
    if c==0:
        print("contact not found") 

def deletedetail():
    name = input("enter name to delete: ")
    p = open("sample1","rb")
    k=pickle.load(p)
    p.close()
    p = open("sample1","wb")
    c=0
    d=0
    for i in k:
        if i[0]==name:
            c=c+1
            k.pop(d)
        d+=1
    if c==0:
        print("record not available")
    print(k)
    pickle.dump(k,p)
    p.close()

def editdetail():
    name = input("enter name whose data needs to be changed :")
    phone = int(input("enter new phone no \npress -1 to retain the old phone: "))
    email = input("enter new email \nneter -1 to retain old email id: ")
    p = open("sample1","rb")
    k=pickle.load(p)
    p.close()
    p = open("sample1","wb")
    c=0
    for i in k:
        if i[0] == name:
            c=c+1
            if phone != -1:
                i[1] == phone
            if email != -1:
                i[2] == email
    if c==0:
        print("record not available")
    pickle.dump(k,p)
    p.close()

def exitdetail():
    print("thank you")
    return

n=0
while n!=5:
    print("CHOOSE A NUMBER: \n1 for adding data \n2 for finding data \n3 for deleting data \n4 for editing data \n5 for exiting: ")
    print()
    n=int(input("enter no: "))
    print()
    if n==1:
        adddetail()
    elif n==2:
        finddetail()
    elif n==3:
        deletedetail()
    elif n==4:
        editdetail()
    elif n==5:
        exitdetail()
    else:
        print("invalid number")
