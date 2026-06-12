#ifndef FUZZY_H
#define FUZZY_H

class Fuzzy
{
public:
    static float triMF(float x, float a, float b, float c);
    static float trapMF(float x, float a, float b, float c, float d);

    static float jarakAman(float jarak);
    static float jarakWaspada(float jarak);
    static float jarakBahaya(float jarak);

    static float tingkatBahaya(float jarak);
};

#endif
