# DeerBio
 1.transfasta\
 Extract the AGCT from a file and output them to another file.\
 usage:click to open the transfasta.exe, then type in the input and output files' FilePath.\
 2.countchar\
 Count each characters number from a file.\
 usage:perl countchar.pl (change the path and filename in the countchar.pl first)\
 3.gapfinder\
 This step process the multiple alignment result in a format which is similar to fasta but without header info - only have one line for each sequence and start with '>'. Generating gap position of each sequence and output their location info separately, this result can be used by CIRCOS for comparative genomics and show the insertion or deletion spot of multiple alignment.\
 4.gapsconsensuser\
 This step process the multiple results from gapfinder and consensus the gap that overlapping or near each other to form a new single large gap position. The result can be used by CIRCOS and plot graph to show the 'insertion hot spot'.\
 5.seperator & delete_column\
 The input is global alignment results similar to fasta but without header info - only have one line for each sequence and start with '>'. This is the step which generate space between characters. After this step, you need to run delete_column.sh to delete the column that have same characters (which aren't SNVs).\
 6.snvfinder\
 Using multiple results from last step (seperator and delete_column) to locate SNVs position of each sequence against the reference (pre-selected). This result can be used by CIRCOS and show the SNVs location of each strand (against the reference).\
 7.snvsdensity\
 Detect snv density via location info from snvfinder results. This step generate a result which can be directly used by CIRCOS and plot comparative genomics graph which shown the SNVs density of certain size of sliding window.\
 Develop by lzlniu(Zelin Li)
