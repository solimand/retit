import string
import os

def main():
    path = dir_path = os.path.dirname(os.path.realpath(__file__))
    studListFile = open(os.path.join(path, "ListaFinale.csv"),"r")
    groupsFile = open(os.path.join(path, "groups.txt"),"r")
    groupsFileNames = open(os.path.join(path, "names.txt"),"w+")

    groups = groupsFile.readlines()             #a line is a group (4 or 5 id)
    students = studListFile.readlines()         #a line is a student (id, name, surname)

    for group in groups:                        #group=4/5 studId
        for studId in group.split():         #a studId
        #for studId in group.split(','):         #a studId
            for student in students:            #student=(id, name, surname)
                if studId in student:
                    groupsFileNames.write(student + ";")
                    #print(student+";")
        groupsFileNames.write('\n\n')
        
    studListFile.close()
    groupsFile.close()
    groupsFileNames.close()

if __name__=="__main__":
    main()