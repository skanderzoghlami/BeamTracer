#ifndef INTERVAL_H
#define INTERVAL_H
class interval {
    public:
    double min, max ;
    interval() : min(infinity) , max(-infinity) {}
    interval(double a, double b ) : min(a) , max(b){}
    bool contains(double x) const {
        return x>=min && x<=max ;
    }
    bool surrounds(double x) const {
        return min < x && x < max ;
    }
    bool size() const {
        return max - min ;
    }
    double clamp(double x) const{
        if (x< min) return min ; 
        if (x> max) return max ; 
        return x ; 
    }
    const static interval empty,universe ;
};

const interval interval::empty = interval(infinity,-infinity); 
const interval interval::universe = interval(-infinity,infinity);

#endif // INTERVAL_H