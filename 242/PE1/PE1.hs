-- Question 1
findInList :: (Eq a) => [a] -> [a] -> [Int]
findInList x y = findInListHelper x y [] 0

findInListHelper [] z s c = s
findInListHelper (x:y) (z:t) s c = if x==z then findInListHelper y t (s++[c]) (c+1)  else findInListHelper (x:y) t s (c+1) 


-- Question 2
findInMatrix :: (Eq a) => [[a]] -> [[a]] -> [[(Int, Int)]]
findInMatrix x y = let {xrow = length x;
                        xcol = numOfColumns x;
                        yrow = length y;
                        ycol = numOfColumns y;
                        } in findInMatrixHelper x y xrow xcol yrow ycol 0 0 0 0 0 0 (genMatrix (xrow-1))

numOfColumns (z:t) = length z

--splitLists n s = if n==0 then ([head s], tail s) else let {(sp1, sp2) = splitLists (n-1) (tail s); } in ((head s):sp1, sp2) 

--Generating an (kind of) empty matrix with the same size as the pattern matrix: 
genMatrix 0 = [[(999,999)]]
genMatrix xrow = [(999,999)]:(genMatrix (xrow-1)) 

--Pushing newly acquired poisitions to their respective places in the solution matrix:
pushPosition 0 s y1 y2 = if(head s) == [(999,999)] then ([(y1,y2)]):(tail s) else ((head s)++[(y1,y2)]):(tail s)
pushPosition x1 s y1 y2 = (head s):(pushPosition (x1-1) (tail s) y1 y2)

findInMatrixHelper x y xrow xcol yrow ycol x_1 x_2 y_1 y_2 c_1 c_2 s = if (((x!!x_1)!!x_2) == ((y!!y_1)!!y_2)) then (
                                                                                        --If you can, go diagonally below and left:
                                                                                        if ((x_1 + 1) < xrow) && ((x_2 - 1) >= 0)
                                                                                            then (
                                                                                                if ((y_1 + 1) < yrow) && ((y_2 - 1) >= 0) 
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol (x_1+1) (x_2-1) (y_1 + 1) (y_2 - 1) c_1 c_2 (pushPosition x_1 s y_1 y_2)
                                                                                                else if (c_2 + 1) < ycol
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol (x_1+1) (x_2-1) 0 (c_2 + 1) c_1 (c_2+1) (pushPosition x_1 s y_1 y_2)
                                                                                                else findInMatrixHelper x y xrow xcol yrow ycol (x_1+1) (x_2-1) (c_2 - ycol + 2) (ycol-1) c_1 (c_2+1) (pushPosition x_1 s y_1 y_2)
                                                                                                )
                                                                                        --If diagonal movement is not possible:
                                                                                        else if (c_1 + 1) < (xrow + xcol - 1) then (
                                                                                            --Check whether you still have untouched columns to traverse or not:
                                                                                            if (c_1 + 1) < xcol
                                                                                                then (
                                                                                                --Also move your current place in the y matrix: 
                                                                                                if ((y_1 + 1) < yrow) && ((y_2 - 1) >= 0) 
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol 0 (c_1+1) (y_1 + 1) (y_2 - 1) (c_1+1) c_2 (pushPosition x_1 s y_1 y_2)
                                                                                                else if (c_2 + 1) < ycol
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol 0 (c_1+1) 0 (c_2 + 1) (c_1+1) (c_2+1) (pushPosition x_1 s y_1 y_2)
                                                                                                else findInMatrixHelper x y xrow xcol yrow ycol 0 (c_1+1) (c_2 - ycol + 2) (ycol-1) (c_1+1) (c_2+1) (pushPosition x_1 s y_1 y_2)
                                                                                                )
                                                                                            --If there are no untouched columns left, keep on exhausting the rows:
                                                                                            else (
                                                                                                if ((y_1 + 1) < yrow) && ((y_2 - 1) >= 0) 
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol (c_1 - xcol + 2) (xcol-1) (y_1 + 1) (y_2 - 1) (c_1+1) c_2 (pushPosition x_1 s y_1 y_2)
                                                                                                else if (c_2 + 1) < ycol
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol (c_1 - xcol + 2) (xcol-1) 0 (c_2 + 1) (c_1+1) (c_2+1) (pushPosition x_1 s y_1 y_2)
                                                                                                else findInMatrixHelper x y xrow xcol yrow ycol (c_1 - xcol + 2) (xcol-1) (c_2 - ycol + 2) (ycol-1) (c_1+1) (c_2+1) (pushPosition x_1 s y_1 y_2)
                                                                                                )
                                                                                                
                                                                                            )
                                                                                        --If there is no possible movement left:
                                                                                        else (pushPosition x_1 s y_1 y_2) )
                                                                        --If you couldn't find the element in this position, move your current pos. in the y matrix:
                                                                        else if ((y_1 + 1) < yrow) && ((y_2 - 1) >= 0)
                                                                            then findInMatrixHelper x y xrow xcol yrow ycol x_1 x_2 (y_1 + 1) (y_2 - 1) c_1 c_2 s
                                                                        else if (c_2 + 1) < (yrow + ycol - 1) then
                                                                            (if (c_2 + 1) < ycol
                                                                                then findInMatrixHelper x y xrow xcol yrow ycol x_1 x_2 0 (c_2 + 1) c_1 (c_2 + 1) s
                                                                            else findInMatrixHelper x y xrow xcol yrow ycol x_1 x_2 (c_2 - ycol + 2) (ycol - 1) c_1 (c_2 + 1) s)
                                                                        else (pushPosition x_1 s y_1 y_2)

{-
findInMatrix x y = let {xrow = length x;
                        xcol = numOfColumns x;
                        yrow = length y;
                        ycol = numOfColumns y;
                        } in findInMatrixHelper x y xrow xcol yrow ycol 0 0 0 0 0 0 []

numOfColumns (z:t) = length z

splitLists n s = if n==0 then ([head s], tail s) else let {(sp1, sp2) = splitLists (n-1) (tail s); } in ((head s):sp1, sp2) 

genMatrix xrow xcol cr s = if (cr < xrow) 
                                then (let {(sp1, sp2) = splitLists (xcol-1) s;
                                        } in (concat sp1):(genMatrix xrow xcol (cr+1) sp2) )
                            else []

findInMatrixHelper x y xrow xcol yrow ycol x_1 x_2 y_1 y_2 c_1 c_2 s = if (((x!!x_1)!!x_2) == ((y!!y_1)!!y_2)) then (
                                                                                        
                                                                                        if ((x_1 + 1) < xrow) && ((x_2 - 1) >= 0)
                                                                                            then (
                                                                                                if ((y_1 + 1) < yrow) && ((y_2 - 1) >= 0) 
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol (x_1+1) (x_2-1) (y_1 + 1) (y_2 - 1) c_1 c_2 (s++[[(y_1,y_2)]])
                                                                                                else if (c_2 + 1) < ycol
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol (x_1+1) (x_2-1) 0 (c_2 + 1) c_1 (c_2+1) (s++[[(y_1,y_2)]])
                                                                                                else findInMatrixHelper x y xrow xcol yrow ycol (x_1+1) (x_2-1) (c_2 - ycol + 2) (ycol-1) c_1 (c_2+1) (s++[[(y_1,y_2)]])
                                                                                                )
                                                                                        
                                                                                        else if (c_1 + 1) < (xrow + xcol - 1) then (
                                                                                            
                                                                                            if (c_1 + 1) < xcol
                                                                                                then (
                                                                                                if ((y_1 + 1) < yrow) && ((y_2 - 1) >= 0) 
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol 0 (c_1+1) (y_1 + 1) (y_2 - 1) (c_1+1) c_2 (s++[[(y_1,y_2)]])
                                                                                                else if (c_2 + 1) < ycol
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol 0 (c_1+1) 0 (c_2 + 1) (c_1+1) (c_2+1) (s++[[(y_1,y_2)]])
                                                                                                else findInMatrixHelper x y xrow xcol yrow ycol 0 (c_1+1) (c_2 - ycol + 2) (ycol-1) (c_1+1) (c_2+1) (s++[[(y_1,y_2)]])
                                                                                                )
                                                                                            else (
                                                                                                if ((y_1 + 1) < yrow) && ((y_2 - 1) >= 0) 
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol (c_1 - xcol + 2) (xcol-1) (y_1 + 1) (y_2 - 1) (c_1+1) c_2 (s++[[(y_1,y_2)]])
                                                                                                else if (c_2 + 1) < ycol
                                                                                                    then findInMatrixHelper x y xrow xcol yrow ycol (c_1 - xcol + 2) (xcol-1) 0 (c_2 + 1) (c_1+1) (c_2+1) (s++[[(y_1,y_2)]])
                                                                                                else findInMatrixHelper x y xrow xcol yrow ycol (c_1 - xcol + 2) (xcol-1) (c_2 - ycol + 2) (ycol-1) (c_1+1) (c_2+1) (s++[[(y_1,y_2)]])
                                                                                                )
                                                                                                
                                                                                            )
                                                                                        else genMatrix xrow xcol 0 (s++[[(y_1,y_2)]]) )
                                                                        else if ((y_1 + 1) < yrow) && ((y_2 - 1) >= 0)
                                                                            then findInMatrixHelper x y xrow xcol yrow ycol x_1 x_2 (y_1 + 1) (y_2 - 1) c_1 c_2 s
                                                                        else if (c_2 + 1) < (yrow + ycol - 1) then
                                                                            (if (c_2 + 1) < ycol
                                                                                then findInMatrixHelper x y xrow xcol yrow ycol x_1 x_2 0 (c_2 + 1) c_1 (c_2 + 1) s
                                                                            else findInMatrixHelper x y xrow xcol yrow ycol x_1 x_2 (c_2 - ycol + 2) (ycol - 1) c_1 (c_2 + 1) s)
                                                                        else genMatrix xrow xcol 0 s
-}
