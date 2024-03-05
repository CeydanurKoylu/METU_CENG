def pattern_search(P,I):
    """
    The function takes in a pattern and an image as arguements.
    It contains several loops which pass a search to find the pattern inside the image.
    The loop structure defines a coordinate system with an origin (i,j) inside the image.
    It then looks for the pattern on those origin points one by one by sliding it on the image.
    If it finds a match on the first character, it checks the next one on the same row. 
    If the next character is not a match, it breaks the loop and searches for the next row of the pattern.
    It runs the same procedure for all rows of the pattern, on the chosen origin point (i,j)
    It finds all the consecutive matches on all the pattern rows, and then finds the number of them.
    If the number of matches is equal to the area of the pattern, we found the pattern inside the image, 
    and the function returns the origin points for the pattern and the angle of rotation.
    If not, it rotates the pattern 90 degrees clockwise, checks to see if the pattern exceeds the desired row/column size.
    Then applies the same steps for the rotated pattern as well.
    At the end, if there is no match for the pattern in all rotations, it returns False.
    """
    def dondur(P):
        return [[P[m][n] for m in list(range(len(P)-1,-1,-1))] for n in list(range(len(P[0])))]
    #dondur returns the 90 degrees rotated matrix, as groups of lists in a list   
    H = len(I)
    W = len(I[0])
    N = len(P)
    M = len(P[0])
    
    for i in list(range(H-N+1)):
        for j in list(range(W-M+1)):
            matches = 0
            for k in list(range(N)):
                for l in list(range(M)):
                    if P[k][l] == I[i+k][j+l]:
                        matches += 1
                    else: break
                    if matches == N*M:
                        return (i,j,0)
    P = dondur(P)
    N = len(P)
    M = len(P[0])
    if W >= M and H >= N:
        for i in list(range(H-N+1)):
            for j in list(range(W-M+1)):
                matches = 0
                for k in list(range(N)):
                    for l in list(range(M)):
                        if P[k][l] == I[i+k][j+l]:
                            matches += 1
                        else: break
                        if matches == N*M:
                            return (i,j,90)
    P = dondur(P)
    N = len(P)
    M = len(P[0])
    if W >= M and H >= N:
        for i in list(range(H-N+1)):
            for j in list(range(W-M+1)):
                matches = 0
                for k in list(range(N)):
                    for l in list(range(M)):
                        if P[k][l] == I[i+k][j+l]:
                            matches += 1
                        else: break
                        if matches == N*M:
                            return (i,j,180)
    P = dondur(P)
    N = len(P)
    M = len(P[0])
    if W >= M and H >= N:
        for i in list(range(H-N+1)):
            for j in list(range(W-M+1)):
                matches = 0
                for k in list(range(N)):
                    for l in list(range(M)):
                        if P[k][l] == I[i+k][j+l]:
                            matches += 1
                        else: break
                        if matches == N*M:
                            return (i,j,270)
    return False
