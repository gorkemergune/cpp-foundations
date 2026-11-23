// ============================================================================
//  Lab 06 · std::array and your first function template          DO NOT EDIT
//  The templates (A, B, V) live in lab06_templates.h: a template's body must be
//  visible wherever it is used, so it goes in a header, not in a .cpp file.
// ============================================================================
#pragma once

#include <array>
#include <vector>

struct WeekStats {
    int minTemp;
    int maxTemp;
    double average;
    int warmestDay;   // index 0..6 of the FIRST day with maxTemp
};

// L06-M · Main · statistics of one week of temperatures.
WeekStats weekStats(const std::array<int, 7>& t);

// L06-X · Optional · LeetCode 1550: three odd numbers next to each other?
bool threeConsecutiveOdds(const std::vector<int>& arr);
