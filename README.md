To make it easier to generate histograms from a series of pull tests, I created a collection of scripts.

It requires a working installation of root and awk.

Usage:
- Go into that directory
- Store the csv file with your test results in there
- Invoke it by ./plotPullTestResults.sh [yourResultFile.csv]
- For every test series, a file plotPullTest_I.pdf is created, where I is the number of the test inside the csv file
- If run for the first time, root will have to compile the macro. Give it a few seconds patience.
- The titles are taken from the comments inside the csv. If you are not happy with them, edit the file.

