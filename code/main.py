import sys
import os

# Extract data from the headset
#os.system("dataExtraction\\dataExtraction.exe dataExtraction\\output.txt")

if(len(sys.argv)>1):
	# Class label is provided

	print("Performing SVD and PCA...")

	# Perform singular value decomposition on the data
	os.system("svd\\svd.exe dataExtraction\\output.txt svd\\sampleoutput.txt "+sys.argv[1])

	# Open training Data Set file and create it if it does not exist
	if(os.path.exists("temp\\trainingDataset.txt")):
		trainingDatasetFile = open("temp\\trainingDataset.txt","a")
		trainingDatasetFile.write("\n")
	else:
		trainingDatasetFile = open("temp\\trainingDataset.txt","w")

	# Open the file containing the output of SVD
	svdOutputFile = open("svd\\sampleoutput.txt")

	# Append SVD lines to Data Set
	for svdLine in svdOutputFile:
		trainingDatasetFile.write(svdLine)
	
	# Close file handles
	trainingDatasetFile.close()
	svdOutputFile.close()
else:
	# No class label is provided

	print("Performing SVD and PCA...")

	# Perform singular value decomposition on the data
	os.system("svd\\svd.exe dataExtraction\\output.txt svd\\sampleoutput.txt ")

	# Check if the training data set exists
	if(not os.path.exists("temp\\trainingDataset.txt")):
		# Training data set dies not exist, exit
		print("Training data set not found. Exiting")
		exit()

	print("Classifying...")

	# Classify the test data
	os.system("C:\\Python27\\python classification\\nearestNeighbour.py temp\\trainingDataset.txt svd\\sampleoutput.txt")