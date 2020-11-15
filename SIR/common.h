#pragma once

typedef struct
{
    float s;
    float i;
    float r;
} Day;

typedef struct
{
    Day *sir;
    int days;
    int infectious_days;
    float infections_per_day;
} Data;