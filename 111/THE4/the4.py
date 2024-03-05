def construct_forest(lst):
    real_lst = []
    #Organises the given elements, terminates the gaps.
    for element in lst:
        current = ""
        for object in element:
            if object != " ":
                current += object
        real_lst.append(current)
    results = []
    terms = []
    functions = []
    #Creates two different lists, one for keeping the functions' names, other for keeping the terms.
    for el in real_lst:
        func = el[:4]
        functions.append(func)
    for element in real_lst:
        found = 0
        for i in range(len(element)):
            if element[i] == "+" or element[i] == "^" or element[i] == "*" or element[i] == "-" : 
                found = i 
        term1 = element[5:found]
        term2 = element[found + 1:]
        terms.append([term1,term2])
    lst1 = []
    lst2 = []
    lst3 = []
    lst4 = []
    lst1f = []
    #Organises the given functions, checks if their terms contain functions or not.
    for i in range(len(terms)):
        if terms[i][0] not in functions and terms[i][1] not in functions:
            lst1f.append(real_lst[i][0:4])
            lst1.append(real_lst[i])
        if terms[i][0] not in functions and terms[i][1] in functions:
            lst2.append(real_lst[i])
        if terms[i][0] in functions and terms[i][1] not in functions:
            lst3.append(real_lst[i])
        if terms[i][0] in functions and terms[i][1] in functions:
            lst4.append(real_lst[i])
    x = lst1f
    real_lst = lst1
    #This process makes sure there are no functions that are in the terms of another, before they were defined.
    while lst2 != [] or lst3 != [] or lst4 != []:
        if lst2 != []:
            for object in lst2:
                for i in range(len(object)):
                    if object[i] == "+" or object[i] == "^" or object[i] == "*" or object[i] == "-" : 
                        found = i 
                term2 = object[found + 1:]
                
                if term2 in x:
                    real_lst.append(object)
                    x.append(object[:4])
                    lst2.remove(object) 
        if lst3 != []:
            for object in lst3:
                for i in range(len(object)):
                    if object[i] == "+" or object[i] == "^" or object[i] == "*" or object[i] == "-" : 
                        found = i 
                term1 = object[5:found]
                
                if term1 in x:
                    real_lst.append(object)
                    x.append(object[:4])
                    lst3.remove(object) 
        if lst4 != []:
            for object in lst4:
                for i in range(len(object)):
                    if object[i] == "+" or object[i] == "^" or object[i] == "*" or object[i] == "-" : 
                        found = i 
                term1 = object[5:found]
                term2 = object[found + 1:]
                
                if term1 in x and term2 in x:
                    real_lst.append(object)
                    x.append(object[:4])
                    lst4.remove(object)
    #And finally, we implement the tree structure and plug in the functions where they are needed.
    for element in real_lst:
        function = element[0]
        found = 0
        for i in range(len(element)):
            if element[i] == "+" or element[i] == "^" or element[i] == "*" or element[i] == "-" : 
                found = i 
        operator = element[found]
        term1 = element[5:found]
        term2 = element[found + 1:]
        terms.append([term1,term2])
        if term1 not in functions and term2 not in functions:
            results.append([function, operator, [term1], [term2]])
        else:
            if term1 in functions:
                for i in range(len(results)):
                    if results[i][0] == term1[0]:
                        term1 = results[i]
                        del results[i]
                        break
            else: term1 = [term1]
            if term2 in functions:
                for j in range(len(results)):
                    if results[j][0] == term2[0]:
                        term2 = results[j]
                        del results[j]
                        break
            else: term2 = [term2]
            results.append([function, operator, term1, term2])
    return results
