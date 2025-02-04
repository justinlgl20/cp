def findXorSum(arr, n):
     
    # variable to store the final Sum
    Sum = 0
 
    # multiplier
    mul = 1
 
    for i in range(30):
 
        # variable to store number of sub-arrays
        # with odd number of elements with ith
        # bits starting from the first element
        # to the end of the array
        c_odd = 0
 
        # variable to check the status of the
        # odd-even count while calculating c_odd
        odd = 0
 
        # loop to calculate initial
        # value of c_odd
        for j in range(n):
            if ((arr[j] & (1 << i)) > 0):
                odd = (~odd)
            if (odd):
                c_odd += 1
         
        # loop to iterate through all the
        # elements of the array and update Sum
        for j in range(n):
            Sum += (mul * c_odd)
 
            if ((arr[j] & (1 << i)) > 0):
                c_odd = (n - j - c_odd)
 
        # updating the multiplier
        mul *= 2
     
    # returning the Sum
    return Sum
 
# Driver Code
arr = [1, 3, 2]
 
n = len(arr)
 
print(findXorSum(arr, n))
