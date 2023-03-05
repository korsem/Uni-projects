# School Logbook
This Program prints information about a student/students with the highest average grade from school and prints how many students get certain number of prices.
Prices are given on a certain criterium:
highest average grade in school, highest average grade in a group, highest number of grades >= 5 and behavior grade = 6.

The homework task was to create two classes: Group and Student.
Class Students stores information about:
student's ID (unique number for each Student),
number of given Prices,
a list of the grades obtained (range of each grade 1-6),
number of grades

Group is the class which stores indicators on Students in the Group and current number of Students in the group (max number of 30) and groupID.

Information about the students is read from a file, where each row in the file is in given form:
[GroupID] [Grade on behavior] [number of grades] [grade_1] [grade_2] ... [grade_n] - where 'n' is the number of grades

Addictionally, most important methods in a class Student are:
avgGrade() - calculates average of Student's grade,
fillOutGrades() - takes a string which is a row from my file, which contains student's grades and assigns it to a Student,
givePrice(), goodGrade() - subsidiary methods for giving out the prices,
thisStudent() - prints out the information about a student

Similarly, most important methods in a class Group are:
newStudent() - adds a Student to the Group. When the Group is full(30 students are already in the group), the candidate fr a student is swapped with a student of the lowest avg grade (if the cantidate has a lower grade he is ignored).
avgBest() - subdiary method for finding the highest average of grades in a grup
thisGroup() - prints out the information about a group,

It is worth noting that in my program main I create the array of 8 Groups which represents school.

# What I have learned
This projects taught me a lot about the classes and indicators, and tables of indicators, and that it is good to take some brakes during a day from coding.
