// ============================================================================
//  Mini Project 06 · Emergency room triage on your own binary heap   DO NOT EDIT
//  Higher severity is treated first; equal severities in order of arrival.
//  Names are unique among the waiting patients.
// ============================================================================
#ifndef TRIAGE_H
#define TRIAGE_H

#include <string>
#include <vector>

class Triage {
public:
    // P06-A
    void arrive(const std::string& name, int severity);
    bool peek(std::string& name) const;            // who is next; false if nobody waits
    bool treat(std::string& name);                 // remove the next patient
    int waiting() const;

    // P06-B · the severity of a waiting patient rises (a smaller or equal value: false);
    // a patient leaves without treatment. Unknown name: false.
    bool upgrade(const std::string& name, int newSeverity);
    bool leave(const std::string& name);

    // P06-C · everybody in treatment order, as "name(severity)" separated by spaces,
    // without changing the queue.
    std::string report() const;

private:
    struct Patient {
        std::string name;
        int severity;
        long long arrival;
    };
    std::vector<Patient> heap;                     // 0-based, like Lab 43
    long long arrivals = 0;

    static bool before(const Patient& a, const Patient& b);   // is a treated before b?
    void siftUp(int i);
    void siftDown(int i);
    int indexOf(const std::string& name) const;    // -1 if not waiting
    void removeAt(int i);
};

#endif
