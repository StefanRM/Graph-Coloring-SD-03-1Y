# Tudor Berariu, Andrei Casu Pop, 2016

from os import listdir, remove, path, system

TEST_DIR = "./tests/"

def deleteOldOutputs():
    for f in filter(lambda s: s.endswith(".out"), listdir(TEST_DIR)):
        remove(path.join(TEST_DIR, f))

def make():
    system("make")
    assert path.exists("./graphs"), "Missing executable"

def equal(v, error = 0.000001):
    v1, v2 = v
    return abs(float(v1) - float(v2)) < error

def checkStack(outStack, correctStack):
    while len(outStack):
        outLine = outStack.pop()
        found = None
        for correctLine in correctStack:
            cVals, oVals = map(str.split, [correctLine, outLine])
            if len(cVals)==len(oVals) and all(map(equal, zip(cVals,oVals))):
                found = correctLine
                break
        if found is None:
            return False
        correctStack.remove(found)
    return True

def compare(outSeries, correctSeries):
    if len(outSeries) == 0 or len(correctSeries) == 0:
        return len(outSeries) == len(correctSeries)
    getCost = lambda line: float(line.split()[0])
    crtValue = getCost(outSeries[0])
    crtLine = 0
    outStack = []
    correctStack = []
    while crtLine < len(outSeries):
        c = getCost(outSeries[crtLine])
        outStack.append(outSeries[crtLine])
        #print(outSeries[crtLine])
        #print(correctSeries[crtLine])
        correctStack.append(correctSeries[crtLine])
        crtLine = crtLine + 1
    if not checkStack(outStack, correctStack):
        return False
    return True

def testTasks(inFile, outFile, correctFile):
    print("Testul curent: %s" % inFile)

    # Read lines from all files
    fs = map(open, [inFile, outFile, correctFile])
    inLns, outLns, correctLns = map(lambda f: map(str.strip, f.readlines()), fs)

    # Read the number of nodes
    n = int(inLns[0])

    # Read the number of queries for task 1
    t1 = int(inLns[n+2])

    # Checking task 1
    correctNo = 0
    try:
        for j in range(t1):
            if j < len(outLns):
                oVals, cVals = map(str.split, [outLns[j],correctLns[j]])
                if len(oVals)==len(cVals) and all(map(equal, zip(oVals,cVals))):
                    correctNo = correctNo + 1
    except:
        pass

    s1 = float(correctNo) / float(t1)
    print("Scor cerinta 1: %f" % s1)

    # Checking task 2
    t2 = int(inLns[n+3+t1])

    correctNo = 0
    j = t1
    j2 = t1

    try:
        while j < len(outLns):
            k = int(outLns[j])
            k2 = int(correctLns[j2])
            if k == k2:
                j = j + 1
                j2 = j2 + 1
                if compare(outLns[j:j+k], correctLns[j2:j2+k2]):
                    correctNo = correctNo + 1
                j = j + k
                j2 = j2 + k
            else:
                j = j + k + 1
                j2 = j2 + k2 + 1
    except:
        pass

    s2 = float(correctNo) / float(t2)
    print("Scor cerinta 2: %f" % s2)

    for f in fs:
        f.close()

    print("-----------")
    return s1, s2

def checkProgram():
    total1 = 0
    total2 = 0
    testsNo = 0
    for inFileName in filter(lambda s: s.endswith(".in"), listdir(TEST_DIR)):
        correctFileName = inFileName.replace(".in", ".correct")
        outFileName = inFileName.replace(".in", ".out")
        inFile = path.join(TEST_DIR, inFileName)
        outFile = path.join(TEST_DIR, outFileName)
        correctFile = path.join(TEST_DIR, correctFileName)

        assert path.exists(correctFile), "Missing file: %s" % correctFile

        system("./graphs %s %s" % (inFile, outFile))
        assert path.exists(outFile), "Missing output file: %s" % outFile

        try:
            s1, s2 = testTasks(inFile, outFile, correctFile)
        except:
            s1, s2 = 0.0, 0.0
        total1 += s1
        total2 += s2
        testsNo += 1

    total1 /= testsNo
    total2 /= testsNo

    print("Scor total cerinta 1: %2.2f" % (total1))
    print("Scor total cerinta 2: %2.2f" % (total2))
    print("----------")
    print("Nota: %2.2f" % (total1 * 5 + total2 * 5))

if __name__ == "__main__":
    assert path.exists("./tests"), "Missing tests folder"
    deleteOldOutputs()
    make()
    checkProgram()
    deleteOldOutputs()
