#include "CandidateDialog.h"
#include "ui_CandidateDialog.h"

CandidateDialog::CandidateDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::CandidateDialog) {
    ui->setupUi(this);
    setWindowTitle("Кандидат");
}

CandidateDialog::~CandidateDialog() { delete ui; }

void CandidateDialog::setCandidate(const Candidate& c) {
    ui->spinDistrict->setValue(c.getDistrict());
    ui->editName->setText(c.getFullName());
    ui->editParty->setText(c.getParty());
    ui->spinAge->setValue(c.getAge());
    ui->editProfession->setText(c.getProfession());
    ui->spinIncome->setValue(c.getIncome());
}

Candidate CandidateDialog::getCandidate() const {
    return Candidate(
        ui->spinDistrict->value(),
        ui->editName->text().trimmed(),
        ui->editParty->text().trimmed(),
        ui->spinAge->value(),
        ui->editProfession->text().trimmed(),
        ui->spinIncome->value()
    );
}
