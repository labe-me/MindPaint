#ifndef TWEENER_H
#define TWEENER_H

typedef float(*TweenMethod)(const float, const float, const float);

class Tween {
private:
    float* value;
    float from;
    float to;
    unsigned long stamp;
    float duration;
    TweenMethod method;

public:
    Tween(float* value_) : value(value_), from(0), to(0), stamp(0), duration(0), method(0) {
    }

    void update(unsigned long now){
        if (duration <= 0.0f)
            return;
        if (value == 0)
            return;
        float time = 1.0f;
        if (duration > 0.0f)
            time = (now - stamp) / duration;
        if (time > 1.0f)
            time = 1.0f;
        (*value) = method(from, to, time);
        if (time >= 1.0f)
            duration = 0.0f;
    }

    void set(float newValue, float duration_, unsigned long now, TweenMethod m){
        if (duration_ == 0.0f){
            (*value) = newValue;
            duration = 0.0f;
            return;
        }
        if (to == newValue)
            return;
        if (duration > 0.0f){
            // stamp = now;
            to = newValue;
            return;
        }
        from = *value;
        to = newValue;
        duration = duration_;
        stamp = now;
        method = m;
    }
};


class Tweener {
public:
    static float linear(const float from, const float to, const float time){
        if (time <= 0.0f)
            return from;
        else if (time >= 1.0f)
            return to;
        return from + (to - from)*time;
    }
};

#endif // TWEENER_H
