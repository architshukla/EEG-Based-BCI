import sys
import speech

if(len(sys.argv)<3):
	print("USAGE: nearestNeighbour.py TraingDataFile TestDataFile")
	exit()

from sklearn.neighbors import KNeighborsClassifier
neigh = KNeighborsClassifier(20,"distance")

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

trainFile.close()

neigh.fit(X,y)

classesPredicted={}

for testLine in testFile:
	testValues = testLine.split(",")
	predictedValue = neigh.predict(testValues)
	if(predictedValue[0] not in classesPredicted):
		classesPredicted[predictedValue[0]] = 1;
	else:
		classesPredicted[predictedValue[0]] += 1;

print("\nClassification: "+str(classesPredicted))

maxKey = classesPredicted.keys()[0]

for eachClass in classesPredicted:
	if(classesPredicted[maxKey] < classesPredicted[eachClass]):
		maxKey = eachClass

print("The object is: "+str(maxKey))

speech.say("You are looking at a "+str(maxKey))

testFile.close()