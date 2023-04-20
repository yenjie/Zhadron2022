var1_list = [60, 80, 100, 120, 150, 200, 250]
var2_list = [0.5, 1, 2]

var1_str_list = [str(x) for x in var1_list]
var2_str_list = [str(x) for x in var2_list]

for var1 in var1_str_list:
    for var2 in var2_str_list:
        print "root -l -q -b \"compareDataMCLoop.C+("+var1+", "+var2+");\""