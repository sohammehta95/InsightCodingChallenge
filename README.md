# InsightCodingChallenge
A coding challenge for Insight Data Science


## Approach
The coding question required us to find the maximum occupations and states where H1B visa was Certified. The first step was to parse the csv and get all the relevant columns. These columns are also not uniform in every year's spreadsheet and also not named uniquely. I have taken account of all the column names used since 2012. If the column name is not found then the user is intimated directly in the start.

Once the relevant columns are extracted, a HashMap is used to store the count of each occupation and state(Unordered_Map in CPP for O(1) retrivals). Next, these map values are put in a heap to find the largest values of each category. Instead of Max Heap, I chose to store the results in a Min Heap so that I need to store only 10 values in the heap at any point of time. This signifacantly reduces the storage and time complexity to O(Nlog10) instead of O(NlogN).

A lot of edge cases are taken care of while writing the code. One of them being that state values occur in multiple ways i.e. both full names and abbreviations. This is handled by unifying the data by only keeping abbreviations.The results are then simply exported to a file in a reverse manner since the heap is inverted. Column names and Percentage values are calculated accordingly while printing to the file. The files follow the same semi-colon delimitted format.

## Running the Code
1. Put the required ".csv" file in the input folder with the name "h1b_counting.cpp"
2. Open Terminal and run the shell script by "./run.sh"

## Note
run.sh file first compiles the CPP code in src folder and creates an excecutable object
While running the program, 3 arguments are passed
1. Path to the input file i.e h1b_input.csv
2. Path to the output occupation file i.e top_10_occupations.txt
3. Path to the output states file i.e top_10_states.txt


## References
1. Parsing CSV in CPP: https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
2. Rounding Float and MAking String : https://stackoverflow.com/questions/1343890/rounding-number-to-2-decimal-places-in-c