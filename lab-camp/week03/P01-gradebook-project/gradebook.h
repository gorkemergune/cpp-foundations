// ============================================================================
//  Mini Project 01 · Gradebook                                      DO NOT EDIT
//  Reads "name score" lines, rejects bad lines, answers questions, prints a report.
// ============================================================================
#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include <istream>
#include <string>
#include <vector>

struct Record {
    std::string name;
    int score;
};

class Gradebook {
public:
    // P01-A · one line "name score": exactly two tokens, name made of letters,
    // score an integer 0..100. Valid -> stored, true. Otherwise -> rejected, false.
    bool addLine(const std::string& line);

    // P01-A · read every line of the stream with addLine; return how many were rejected.
    int readAll(std::istream& in);

    int count() const;              // P01-B · stored records
    double average() const;         // P01-B · 0 if empty
    std::string best() const;       // P01-B · highest score, first on a tie; "" if empty
    // P01-C · names with score < threshold, in input order
    std::vector<std::string> failing(int threshold) const;

    // P01-C · the report, exactly:
    //   students: 3
    //   average: 71.67
    //   best: Ada (95)
    //   failing (<60): Bob
    // ("failing (<60): -" when nobody fails; for an empty book only "students: 0").
    std::string report(int threshold) const;

private:
    std::vector<Record> records_;
};

#endif
