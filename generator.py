#!/usr/bin/python
# -*- coding: UTF-8 -*-

from math import *
from pylab import *
import random, sys, getopt,cv2


def computeDistance(a, b):
    (xa, ya) = a
    (xb, yb) = b
    distance = sqrt((xa-xb)*(xa-xb) + (ya-yb)*(ya-yb))
    return round(distance,2)

def computeDistances(points):
    distances = []
    for i in range(len(points)): # punto A
        distances.append([]);
        for j in range(len(points)): # punto B
            distances[i].append(computeDistance(points[i], points[j]))
        print distances[i]

    for i in range(len(points)):
        for j in range(i+1, len(points)):
            assert distances[i][j] == distances[j][i], "Matrice delle distanze non simmetrica"
    return distances


def printPointsFile(fileName, W, H, points):
    outFile = open(fileName+"_points.txt", "w")
    outFile.write(str(W)+"\n")
    outFile.write(str(H)+"\n")
    for i in range(len(points)):
        x,y = points[i]
        outFile.write(str(x) + " " + str(y)+ "\n")
    outFile.close()

def printDistancesFile(fileName, distances):
    outFile = open(fileName+"_distances.txt", "w")
    outFile.write(str(len(distances))+"\n")
    for i in range(len(distances)):
        for j in range(len(distances)):
            outFile.write(str(distances[i][j])+ " ")
        outFile.write("\n")
    outFile.close()

def printIstanceToFile(istanceName, W, H, points, distances):
    outFile = open(istanceName+".ist", "w")
    outFile.write(str(len(distances))+"\n") # N
    outFile.write(str(W)+"\n") # W
    outFile.write(str(H)+"\n") # H
    for i in range(len(points)): # Punti
        x,y = points[i]
        outFile.write(str(x) + " " + str(y)+ "\n")
    for i in range(len(distances)):
        for j in range(len(distances)):
            outFile.write(str(distances[i][j])+ " ")
        outFile.write("\n")
    outFile.close()

def generateRandomInstance(N):
    H = random.randint(floor(2*sqrt(N)), 2*N) 
    W = random.randint(floor(2*sqrt(N)), 2*N)
    
    points = []
    for i in range(N):
        while True:
            point = (random.randint(0, W), random.randint(0, H))
            if not point in points:
                points.append(point)
                break
    assert len(points) == N, "Non ci sono tutti i punti"
    assert len(points) == len(set(points)), "Ci sono duplicati"
    distances = computeDistances(points)
    return (W, H, points, distances)

# pairs = numero di coppie
# isVertical = il blocco è in verticale?
# point = (x,y) = upper-left corner del blocco
# un blocco è una serie di punti del tipo
#
#     verticale   orizzontale
#       x--x        x-x-x-x
#       |  |        | | | |
#       x--x        | | | |
#       |  |        x-x-x-x
#       x--x        
def buildBlock(pairs, isVertical, point):
    block = []
    startX, startY = point
    for p in range(pairs):
        if isVertical:
            block.append( (startX   , startY + p) )
            block.append( (startX +2, startY + p) )
        else:
            block.append( (startX + p, startY    ) )
            block.append( (startX + p, startY + 2) )
    assert len(block) == 2*pairs
    return block

# ritorna True se almeno un punto del blocco è già presente dentro points
def checkOverlap(points, block):
    for p in points:
        if p in block:
            return True
    return False

def generatePseudoRandomInstance(N):
    H = random.randint(floor(2*sqrt(N)), 2*N) 
    W = random.randint(floor(2*sqrt(N)), 2*N)
    oneMore = N%2 ==1
    if (oneMore): N = N-1 # mi serve un N pari, l'ultimo punto lo aggiungo dopo
    pairs = N/2
    numBlocks = random.randint(1, pairs) # numero di blocchi (agglomerati di punti vicini)
    print "Blocchi da generare: ", numBlocks
    points = []
    extraPairs = pairs - numBlocks # ogni blocco deve essere fatto da almeno una coppia di punti
                                   # le coppie extra vengono usate per creare dei blocchi di dimensione casuale
    for i in range(numBlocks):
        while True:
            extra = random.randint(0, extraPairs)
            if (i == numBlocks-1): extra = extraPairs # se è l'ultimo blocco da costruire uso tutte le coppie extra
            extraPairs = extraPairs - extra
            isVertical = random.choice([True, False])
            start = (random.randint(0, W), random.randint(0, H))
            block = buildBlock(1+extra, isVertical, start)
            if not checkOverlap(points, block):
                print "Verticale" if isVertical else "Orizzontale"
                print block
                print "--------"
                points = points + block
                break

    assert extraPairs == 0
    assert len(points) == N
    if oneMore:
        while True:
            extraPoint = (random.randint(0, W), random.randint(0, H))
            if not extraPoint in points:
                points.append(extraPoint)
                break
    distances = computeDistances(points)
    return (W, H, points, distances)


def generateInstanceFromImage(imageName):
    img = cv2.imread(imageName,0);
    cimg = cv2.cvtColor(img,cv2.COLOR_GRAY2BGR);
    H, W = img.shape
    # http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html
    circles = cv2.HoughCircles(img,cv2.cv.CV_HOUGH_GRADIENT,2,10,param1=100,param2=30,minRadius=4,maxRadius=14);
    circles = np.uint16(np.around(circles));
    points = []
    for i in circles[0,:]:
        cv2.circle(cimg,(i[0],i[1]),2,(0,0,255),3);
        assert i[0] >= 0 and i[0] <= W, "Punto fuori dalla scheda"
        assert i[1] >= 0 and i[1] <= H, "Punto fuori dalla scheda"
        points.append((i[0], i[1]))
    cv2.imwrite('detected-%s'%(imageName),cimg)
    print "%d fori trovati."%(len(circles[0]));

    assert len(points) == len(set(points)), "Ci sono duplicati"

    distances = computeDistances(points)
    return (W, H, points, distances)

def main(argv):

    try:
        (opts, args) = getopt.getopt(argv,"hn:i:f:p")
    except getopt.GetoptError, e:
        print "generator.py -n <n> -f <instanceName> [-p]"
        print "generator.py -i <imageFilePath> -f <instanceName>"
        print e
        sys.exit(2)

    pseudo = False
    imagePath = ""
    fileName = "generatedInstance"
    N = 0
    for opt, arg in opts:
        if opt == "-h":
            print "USAGE:"
            print "generator.py -n <n> -f <instanceName> [-p]"
            print "generator.py -i <imageFilePath> -f <instanceName>"
            sys.exit()
        elif opt in ("-n", "--num"):
            print arg
            N = int(arg)
        elif opt in ("-i", "--image"):
            imagePath = arg
        elif opt in ("-f", "--fname"):
            fileName = arg
        elif opt in ("-p", "--pseudo"):
            pseudo = True
    
    if N != 0:
        (W, H, points, distances) = generateRandomInstance(N) if not pseudo else generatePseudoRandomInstance(N)
    else:
        assert imagePath != "", "Non è stata specificata un'immagine"
        (W, H, points, distances) = generateInstanceFromImage(imagePath)

    print "Larghezza: ",W, "Altezza: " ,H, "#Points: ", len(points) 
    print points

    printPointsFile(fileName, W, H, points)
    printDistancesFile(fileName, distances)
    #printIstanceToFile(fileName, W, H, points, distances)

if __name__ == '__main__':
    main(sys.argv[1:])   