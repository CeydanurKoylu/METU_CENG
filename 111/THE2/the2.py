input_values = eval(input())

x_1 = input_values[0][0]
y_1 = input_values[0][1]

x_2 = input_values[1][0]
y_2 = input_values[1][1]

x_3 = input_values[2][0]
y_3 = input_values[2][1]

x_4 = input_values[3][0]
y_4 = input_values[3][1]

max_x_input = max(x_1,x_2,x_3,x_4)
min_x_input = min(x_1,x_2,x_3,x_4)
max_y_input = max(y_1,y_2,y_3,y_4)
min_y_input = min(y_1,y_2,y_3,y_4)


if min_y_input>=0:
    #For the 4 point case
    if x_1 == min_x_input and x_4 == max_x_input:
        result = abs(((x_1*y_1)+(x_1*y_4))-((y_1*x_4)+(y_4*x_4)))/2
        print("%.2f" % result)
    elif x_2 == min_x_input and x_1 == max_x_input:
        result = abs(((x_2*y_2)+(x_2*y_1))-((y_2*x_1)+(y_1*x_1)))/2
        print("%.2f" % result)
    elif x_3 == min_x_input and x_2 == max_x_input:
        result = abs(((x_3*y_3)+(x_3*y_2))-((y_3*x_2)+(y_2*x_2)))/2
        print("%.2f" % result)
    elif x_4 == min_x_input and x_3 == max_x_input:
        result = abs(((x_4*y_4)+(x_4*y_3))-((y_4*x_3)+(y_3*x_3)))/2
        print("%.2f" % result)
    #For the 5 point case
    elif x_1 == min_x_input and x_3 == max_x_input:
        result = abs(((x_1*y_1)+(x_1*y_4)+(x_4*y_3))-((y_1*x_4)+(y_4*x_3)+(y_3*x_3)))/2
        print("%.2f" % result)
    elif x_2 == min_x_input and x_4 == max_x_input:
        result = abs(((x_2*y_2)+(x_2*y_1)+(x_1*y_4))-((y_2*x_1)+(y_1*x_4)+(y_4*x_4)))/2
        print("%.2f" % result)
    elif x_3 == min_x_input and x_1 == max_x_input:
        result = abs(((x_3*y_3)+(x_3*y_2)+(x_2*y_1))-((y_3*x_2)+(y_2*x_1)+(y_1*x_1)))/2
        print("%.2f" % result)
    elif x_4 == min_x_input and x_2 == max_x_input:
        result = abs(((x_4*y_4)+(x_4*y_3)+(x_3*y_2))-((y_4*x_3)+(y_3*x_2)+(y_2*x_2)))/2
        print("%.2f" % result)
    #For the 6 point case
    elif x_1 == min_x_input and x_2 == max_x_input:
        result = (abs(((x_1*y_1)+(x_1*y_4)+(x_4*y_3)+(x_3*y_2))-((y_1*x_4)+(y_4*x_3)+(y_3*x_2)+(y_2*x_2))))/2
        print("%.2f" % result)
    elif x_2 == min_x_input and x_3 == max_x_input:
        result = (abs(((x_2*y_2)+(x_2*y_1)+(x_1*y_4)+(x_4*y_3))-((y_2*x_1)+(y_1*x_4)+(y_4*x_3)+(y_3*x_3))))/2
        print("%.2f" % result)
    elif x_3 == min_x_input and x_4 == max_x_input:
        result = (abs(((x_3*y_3)+(x_3*y_2)+(x_2*y_1)+(x_1*y_4))-((y_3*x_2)+(y_2*x_1)+(y_1*x_4)+(y_4*x_4))))/2
        print("%.2f" % result)
    elif x_4 == min_x_input and x_1 == max_x_input:
        result = (abs(((x_4*y_4)+(x_4*y_3)+(x_3*y_2)+(x_2*y_1))-((y_4*x_3)+(y_3*x_2)+(y_2*x_1)+(y_1*x_1))))/2
        print("%.2f" % result)
    


elif max_y_input<=0:
    #For the 4 point case
    if x_1 == min_x_input and x_2 == max_x_input:
        result = abs(((x_1*y_1)+(x_1*y_2))-((y_1*x_2)+(y_2*x_2)))/2
        print("%.2f" % result)
    elif x_2 == min_x_input and x_3 == max_x_input:
        result = abs(((x_2*y_2)+(x_2*y_3))-((y_2*x_3)+(y_3*x_3)))/2
        print("%.2f" % result)
    elif x_3 == min_x_input and x_4 == max_x_input:
        result = abs(((x_3*y_3)+(x_3*y_4))-((y_3*x_4)+(y_4*x_4)))/2
        print("%.2f" % result)
    elif x_4 == min_x_input and x_1 == max_x_input:
        result = abs(((x_4*y_4)+(x_4*y_1))-((y_4*x_1)+(y_1*x_1)))/2
        print("%.2f" % result)   
    #For the 5 point case
    elif x_1 == min_x_input and x_3 == max_x_input:
        result = abs(((x_1*y_1)+(x_1*y_2)+(x_2*y_3))-((y_1*x_2)+(y_2*x_3)+(y_3*x_3)))/2
        print("%.2f" % result)
    elif x_2 == min_x_input and x_4 == max_x_input:
        result = abs(((x_2*y_2)+(x_2*y_3)+(x_3*y_4))-((y_2*x_3)+(y_3*x_4)+(y_4*x_4)))/2
        print("%.2f" % result)
    elif x_3 == min_x_input and x_1 == max_x_input:
        result = abs(((x_3*y_3)+(x_3*y_4)+(x_4*y_1))-((y_3*x_4)+(y_4*x_1)+(y_1*x_1)))/2
        print("%.2f" % result)
    elif x_4 == min_x_input and x_2 == max_x_input:
        result = abs(((x_4*y_4)+(x_4*y_1)+(x_1*y_2))-((y_4*x_1)+(y_1*x_2)+(y_2*x_2)))/2
        print("%.2f" % result)
#For the 6 point case
    elif x_1 == min_x_input and x_4 == max_x_input:
        result = (abs(((x_2*y_1)+(x_4*y_4)+(x_4*y_3)+(x_3*y_2))-((y_1*x_1)+(y_4*x_3)+(y_3*x_2)+(y_2*x_1))))/2
        print("%.2f" % result)
    elif x_2 == min_x_input and x_1 == max_x_input:
        result = (abs(((x_3*y_2)+(x_1*y_1)+(x_1*y_4)+(x_4*y_3))-((y_2*x_2)+(y_1*x_4)+(y_4*x_3)+(y_3*x_2))))/2
        print("%.2f" % result)
    elif x_3 == min_x_input and x_2 == max_x_input:
        result = (abs(((x_4*y_3)+(x_2*y_2)+(x_2*y_1)+(x_1*y_4))-((y_3*x_3)+(y_2*x_1)+(y_1*x_4)+(y_4*x_3))))/2
        print("%.2f" % result)
    elif x_4 == min_x_input and x_3 == max_x_input:
        result = (abs(((x_1*y_4)+(x_3*y_3)+(x_3*y_2)+(x_2*y_1))-((y_4*x_4)+(y_3*x_2)+(y_2*x_1)+(y_1*x_4))))/2
        print("%.2f" % result)
    

