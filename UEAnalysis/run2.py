var1_list = [10,15, 20,30,40, 60, 80]
var2_list = [0.5,0.8, 1, 2]

var1_str_list = [str(x) for x in var1_list]
var2_str_list = [str(x) for x in var2_list]

for var2 in var2_str_list:
   for var1 in var1_str_list:
        print "root -l -q -b \"compareDataMCLoop.C+("+var1+", "+var2+");\""