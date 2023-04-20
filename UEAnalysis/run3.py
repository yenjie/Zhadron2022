var1_list = [10, 15, 20, 30, 40, 60, 80,120, 200]
var2_list = [0.5, 0.8, 1, 2]

for i in range(len(var1_list)-1):
    var1 = str(var1_list[i])
    next_var1 = str(var1_list[i+1])
    for var2 in var2_list:
        print("root -l -q -b \"compareDataMCLoop.C+("+var1+", "+next_var1+", "+str(var2)+");\"")
