import heapq

class MedianMaintainer:
    def __init__(self):
        self.lower = []
        self.upper = []
        
    def addValue(self, value):
        try:
            if value > -self.lower[0]:
                heapq.heappush(self.upper, value)
            else:
                heapq.heappush(self.lower, -value)
        except IndexError:
            heapq.heappush(self.lower, -value)

        if len(self.upper) == len(self.lower)+2:
            heapq.heappush(self.lower, -heapq.heappop(self.upper))

        elif len(self.upper)+2 == len(self.lower):
            heapq.heappush(self.upper, -heapq.heappop(self.lower))


    def getMedian(self):
        if len(self.upper) == len(self.lower) or len(self.upper) < len(self.lower):
            return -self.lower[0]
        return self.upper[0]
