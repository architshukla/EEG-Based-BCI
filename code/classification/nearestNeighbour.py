import sys

if(len(sys.argv)<3):
	print("USAGE: nearestNeighbour.py TraingDataFile TestDataFile")
	exit()

from sklearn.neighbors import KNeighborsClassifier
neigh = KNeighborsClassifier(5,"distance")

trainFile = open(sys.argv[1])
testFile = open(sys.argv[2])

y=[]
X=[]

for trainLine in trainFile:
	parts = trainLine.split("|")
	parts[1] = parts[1].rstrip();
	y.append(parts[1])
	numbers = parts[0].split(",")
	X.append(numbers)

# print("\nY is "+str(y))
# print("\nX is "+str(X))

neigh.fit(X,y)

for testLine in testFile:
	testValues = testLine.split(",")
	print("\nPREDICTION: ")
	print(neigh.predict(testValues))