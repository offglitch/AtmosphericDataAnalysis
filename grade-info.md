# Grade Information

## Test 1: Compilation

No dead/leftover/unnecessary code should be highlighted here. [1 pts]

```
+ gcc -g -Wall climate.c -o climate
+ test_end
+ return=0
+ [Output Lines: 0]
```

## Test 2: No Args

Program should gracefully exit with no arguments [1 pts]

```
+ ./climate
number arguments = 1
Usage: ./climate tdv_file1 tdv_file2 ... tdv_fileN 
+ test_end
+ return=1
+ [Output Lines: 2]
```

## Test 3: Missing File

Program should gracefully exit and print an error message [1 pts]

```
+ ./climate this_file_should_not_exist.tdv
number arguments = 2
Opening file: this_file_should_not_exist.tdv
File this_file_should_not_exist.tdv does not exist
States found: 
+ test_end
+ return=0
+ [Output Lines: 4]
```

## Test 4: Use perror to report file errors

```
+ grep -A2 -B2 perror climate.c
+ test_end
+ return=1
+ [Output Lines: 0]
```

## Test 5: Use of memory allocation functions

```
+ grep -A2 -B2 .alloc climate.c
         *         code, stored as our first token.
         *       * If our states array doesn't have a climate_info entry for
         *         this state, then we need to allocate memory for it and put it
         *         in the next open place in the array. Otherwise, we reuse the
         *         existing entry.
--
--
        if(flag == 0) 
        {
            info = (struct climate_info *)malloc (sizeof(struct climate_info));
            strcpy(info->code, code);
            info->cloud = cloud_cover;
+ test_end
+ return=0
+ [Output Lines: 12]
```

## Test 6: Tennessee

```
+ ./climate ../../220/p1-files/data_tn.tdv
number arguments = 2
Opening file: ../../220/p1-files/data_tn.tdv
States found: TN 
-- State: TN --
Number of Records: 17097
Average Humidity: 49.4
Average Temperature: 58.3F
Max Temperature: 49.4F on Thu Jan  2 08:10:40 1964
Min Temperature: 58.3F on Tue Dec 24 10:03:44 1940
Lightning Strikes: 781
Records with Snow Cover: 107
Average Cloud Cover: 53.0 

+ test_end
+ return=0
+ [Output Lines: 12]
```

## Test 7: Missing File + Valid File

Should still print data for TN [1 pts]

```
+ ./climate this_file_should_not_exist.tdv ../../220/p1-files/data_tn.tdv
number arguments = 3
Opening file: this_file_should_not_exist.tdv
Opening file: ../../220/p1-files/data_tn.tdv
File this_file_should_not_exist.tdv does not exist
States found: TN 
-- State: TN --
Number of Records: 17097
Average Humidity: 49.4
Average Temperature: 58.3F
Max Temperature: 49.4F on Thu Jan  2 08:10:40 1964
Min Temperature: 58.3F on Tue Dec 24 10:03:44 1940
Lightning Strikes: 781
Records with Snow Cover: 107
Average Cloud Cover: 53.0 

+ test_end
+ return=0
+ [Output Lines: 14]
```

## Test 8: Washington

```
+ ./climate ../../220/p1-files/data_wa.tdv
number arguments = 2
Opening file: ../../220/p1-files/data_wa.tdv
States found: WA 
-- State: WA --
Number of Records: 48357
Average Humidity: 61.3
Average Temperature: 52.9F
Max Temperature: 61.3F on Sat Mar 23 14:38:56 2002
Min Temperature: 52.9F on Fri Jan 29 19:14:08 2010
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5 

+ test_end
+ return=0
+ [Output Lines: 12]
```

## Test 9: Single state (WA) split across two files

This output should be the same as the previous test. [1 pts]

```
+ ./climate ../../220/p1-files/data_wa_1.tdv ../../220/p1-files/data_wa_2.tdv
number arguments = 3
Opening file: ../../220/p1-files/data_wa_1.tdv
Opening file: ../../220/p1-files/data_wa_2.tdv
States found: WA 
-- State: WA --
Number of Records: 48357
Average Humidity: 61.3
Average Temperature: 52.9F
Max Temperature: 61.3F on Sat Mar 23 14:38:56 2002
Min Temperature: 52.9F on Fri Jan 29 19:14:08 2010
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5 

+ test_end
+ return=0
+ [Output Lines: 13]
```

## Test 10: Tennessee + Washington

```
+ ./climate ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_wa.tdv
number arguments = 3
Opening file: ../../220/p1-files/data_tn.tdv
Opening file: ../../220/p1-files/data_wa.tdv
States found: TN WA 
-- State: TN --
Number of Records: 17097
Average Humidity: 49.4
Average Temperature: 58.3F
Max Temperature: 49.4F on Thu Jan  2 08:10:40 1964
Min Temperature: 58.3F on Tue Dec 24 10:03:44 1940
Lightning Strikes: 781
Records with Snow Cover: 107
Average Cloud Cover: 53.0 

-- State: WA --
Number of Records: 48357
Average Humidity: 61.3
Average Temperature: 52.9F
Max Temperature: 61.3F on Sat Mar 23 14:38:56 2002
Min Temperature: 52.9F on Fri Jan 29 19:14:08 2010
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5 

+ test_end
+ return=0
+ [Output Lines: 23]
```

## Test 11: Multi State

```
+ ./climate ../../220/p1-files/data_multi.tdv
number arguments = 2
Opening file: ../../220/p1-files/data_multi.tdv
States found: CA CO PA FL LA 
-- State: CA --
Number of Records: 84601
Average Humidity: 38.1
Average Temperature: 62.1F
Max Temperature: 38.1F on Sat Nov  9 08:10:40 1996
Min Temperature: 62.1F on Mon Dec 17 12:45:52 1962
Lightning Strikes: 1616
Records with Snow Cover: 599
Average Cloud Cover: 34.7 

-- State: CO --
Number of Records: 67040
Average Humidity: 60.8
Average Temperature: 49.6F
Max Temperature: 60.8F on Thu Jul  5 08:10:40 1906
Min Temperature: 49.6F on Mon Jul 21 10:03:44 1924
Lightning Strikes: 4763
Records with Snow Cover: 3082
Average Cloud Cover: 40.1 

-- State: PA --
Number of Records: 19526
Average Humidity: 57.4
Average Temperature: 48.8F
Max Temperature: 57.4F on Wed Sep 25 15:38:56 1957
Min Temperature: 48.8F on Sat Dec 29 03:35:28 1962
Lightning Strikes: 667
Records with Snow Cover: 575
Average Cloud Cover: 59.2 

-- State: FL --
Number of Records: 35632
Average Humidity: 38.2
Average Temperature: 76.1F
Max Temperature: 38.2F on Mon May 17 15:38:56 1982
Min Temperature: 76.1F on Tue Dec 24 10:03:44 1940
Lightning Strikes: 1436
Records with Snow Cover: 0
Average Cloud Cover: 39.1 

-- State: LA --
Number of Records: 23350
Average Humidity: 42.1
Average Temperature: 69.0F
Max Temperature: 42.1F on Mon Jan 19 08:10:40 1953
Min Temperature: 69.0F on Thu Apr 18 10:03:44 1940
Lightning Strikes: 814
Records with Snow Cover: 0
Average Cloud Cover: 44.5 

+ test_end
+ return=0
+ [Output Lines: 52]
```

## Test 12: Multi State + TN + WA

```
+ ./climate ../../220/p1-files/data_multi.tdv ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_wa.tdv
number arguments = 4
Opening file: ../../220/p1-files/data_multi.tdv
Opening file: ../../220/p1-files/data_tn.tdv
Opening file: ../../220/p1-files/data_wa.tdv
States found: CA CO PA FL LA TN WA 
-- State: CA --
Number of Records: 84601
Average Humidity: 38.1
Average Temperature: 62.1F
Max Temperature: 38.1F on Sat Nov  9 08:10:40 1996
Min Temperature: 62.1F on Mon Dec 17 12:45:52 1962
Lightning Strikes: 1616
Records with Snow Cover: 599
Average Cloud Cover: 34.7 

-- State: CO --
Number of Records: 67040
Average Humidity: 60.8
Average Temperature: 49.6F
Max Temperature: 60.8F on Thu Jul  5 08:10:40 1906
Min Temperature: 49.6F on Mon Jul 21 10:03:44 1924
Lightning Strikes: 4763
Records with Snow Cover: 3082
Average Cloud Cover: 40.1 

-- State: PA --
Number of Records: 19526
Average Humidity: 57.4
Average Temperature: 48.8F
Max Temperature: 57.4F on Wed Sep 25 15:38:56 1957
Min Temperature: 48.8F on Sat Dec 29 03:35:28 1962
Lightning Strikes: 667
Records with Snow Cover: 575
Average Cloud Cover: 59.2 

-- State: FL --
Number of Records: 35632
Average Humidity: 38.2
Average Temperature: 76.1F
Max Temperature: 38.2F on Mon May 17 15:38:56 1982
Min Temperature: 76.1F on Tue Dec 24 10:03:44 1940
Lightning Strikes: 1436
Records with Snow Cover: 0
Average Cloud Cover: 39.1 

-- State: LA --
Number of Records: 23350
Average Humidity: 42.1
Average Temperature: 69.0F
Max Temperature: 42.1F on Mon Jan 19 08:10:40 1953
Min Temperature: 69.0F on Thu Apr 18 10:03:44 1940
Lightning Strikes: 814
Records with Snow Cover: 0
Average Cloud Cover: 44.5 

-- State: TN --
Number of Records: 17097
Average Humidity: 49.4
Average Temperature: 58.3F
Max Temperature: 49.4F on Thu Jan  2 08:10:40 1964
Min Temperature: 58.3F on Tue Dec 24 10:03:44 1940
Lightning Strikes: 781
Records with Snow Cover: 107
Average Cloud Cover: 53.0 

-- State: WA --
Number of Records: 48357
Average Humidity: 61.3
Average Temperature: 52.9F
Max Temperature: 61.3F on Sat Mar 23 14:38:56 2002
Min Temperature: 52.9F on Fri Jan 29 19:14:08 2010
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5 

+ test_end
+ return=0
+ [Output Lines: 74]
```

## Test 13: File with all Zero Values

```
+ ./climate ../../220/p1-files/data_blank.tdv
number arguments = 2
Opening file: ../../220/p1-files/data_blank.tdv
States found: TX 
-- State: TX --
Number of Records: 14
Average Humidity: 0.0
Average Temperature: -459.7F
Max Temperature: 0.0F on Wed Dec 31 16:00:00 1969
Min Temperature: -459.7F on Wed Dec 31 16:00:00 1969
Lightning Strikes: 0
Records with Snow Cover: 0
Average Cloud Cover: 0.0 

+ test_end
+ return=0
+ [Output Lines: 12]
```

## Test 14: 3x Tennessee

```
+ ./climate ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_tn.tdv
number arguments = 4
Opening file: ../../220/p1-files/data_tn.tdv
Opening file: ../../220/p1-files/data_tn.tdv
Opening file: ../../220/p1-files/data_tn.tdv
States found: TN 
-- State: TN --
Number of Records: 51291
Average Humidity: 49.4
Average Temperature: 58.3F
Max Temperature: 49.4F on Thu Jan  2 08:10:40 1964
Min Temperature: 58.3F on Tue Dec 24 10:03:44 1940
Lightning Strikes: 2343
Records with Snow Cover: 321
Average Cloud Cover: 53.0 

+ test_end
+ return=0
+ [Output Lines: 14]
```


## Deductions

* (Test 4): No perror() [-1]
* Missing function documentation headers [-1]
* Min/max temperatures, dates/times incorrect; in many cases the min temperature is higher than the max. [-3]
* (Test 13): Zero (max temp) [-1]
