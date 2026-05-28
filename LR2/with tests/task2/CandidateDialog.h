#ifndef CANDIDATEDIALOG_H
#define CANDIDATEDIALOG_H

#include <QDialog>
#include "Candidate.h"

namespace Ui { class CandidateDialog; }

class CandidateDialog : public QDialog {
    Q_OBJECT
public:
    CandidateDialog(QWidget* parent = nullptr);
    ~CandidateDialog();

    void setCandidate(const Candidate& c);
    Candidate getCandidate() const;

private:
    Ui::CandidateDialog* ui;
};

#endif // CANDIDATEDIALOG_H
