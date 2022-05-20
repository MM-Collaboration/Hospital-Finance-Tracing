#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    doctorsModel = nullptr;
    patientsModel = nullptr;
    visitsModel = nullptr;
    statModel = nullptr;
    ui->setupUi(this);

    if (createConnection()) {
        qDebug() << "Database connected successfully";
    } else {
        qDebug() << "Database connection error";
    }

    fullNameRegExp = new QRegExp("[A-z,А-я, ,.,-]{50}");
    ui->lineEdit_phoneNumberPatient->setValidator(new QRegExpValidator(QRegExp("(\\+7[1-9]{2}|8|[1-9]{3})([0-9]{8})"), ui->lineEdit_phoneNumberPatient));
    ui->lineEdit_fullNamePatient->setValidator(new QRegExpValidator(*fullNameRegExp, ui->lineEdit_fullNamePatient));
    ui->lineEdit_fullNameDoctor->setValidator(new QRegExpValidator(*fullNameRegExp, ui->lineEdit_fullNameDoctor));

    // Connect actions
    connect(ui->action_openFile, &QAction::triggered, this, &MainWindow::actionOpenFile);
    // Help menu
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::actionAbout);
    connect(ui->action_aboutQt, &QAction::triggered, this, QApplication::aboutQt);

    reloadTableDoctors();
    reloadTablePatients();
    reloadTableVisits();

    updateStat();
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

bool MainWindow::createConnection() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("hospital");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword(""); // empty or 'root' or your password
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    return true;
}

void MainWindow::reloadTableDoctors() {
    if (doctorsModel == nullptr) {
        doctorsModel = new QSqlTableModel();
    }
    doctorsModel->setTable("doctors");
    doctorsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    doctorsModel->select();

    doctorsModel->setHeaderData(1, Qt::Horizontal, tr("Имя"));
    doctorsModel->setHeaderData(2, Qt::Horizontal, tr("Специализация"));
    doctorsModel->setHeaderData(3, Qt::Horizontal, tr("Квалификация"));
    ui->tableView_doctors->hideColumn(0);

    ui->tableView_doctors->setModel(doctorsModel);
    ui->tableView_doctors->setColumnHidden(0, true);
    ui->tableView_doctors->resizeColumnsToContents();

    // set visitDoctors combobox items
    QSqlQuery query("SELECT name FROM doctors");
    while (ui->comboBox_vistDoctor->count() != 0) { // claer comboBox
        ui->comboBox_vistDoctor->removeItem(0);
    }
    while (query.next()) {
        QString name = query.value(0).toString();
        qDebug() << "Doctor name: " << name;
        ui->comboBox_vistDoctor->addItem(name);
    }
}

void MainWindow::reloadTablePatients() {
    if (patientsModel == nullptr) {
        patientsModel = new QSqlTableModel();
    }
    patientsModel->setTable("patients");
    patientsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    patientsModel->select();

    patientsModel->setHeaderData(1, Qt::Horizontal, tr("Имя"));
    patientsModel->setHeaderData(2, Qt::Horizontal, tr("Год рождения"));
    patientsModel->setHeaderData(3, Qt::Horizontal, tr("Телефон"));

    ui->tableView_patients->setModel(patientsModel);
    ui->tableView_patients->setColumnHidden(0, true);
    ui->tableView_patients->resizeColumnsToContents();

    // set visitPatients combobox items
    QSqlQuery query("SELECT name FROM patients");
    while (ui->comboBox_vistPatient->count() != 0) { // claer comboBox
        ui->comboBox_vistPatient->removeItem(0);
    }
    while (query.next()) {
        QString name = query.value(0).toString();
        qDebug() << "Patient name: " << name;
        ui->comboBox_vistPatient->addItem(name);
    }
}

void MainWindow::reloadTableVisits() {
    if (visitsModel == nullptr) {
        visitsModel = new QSqlRelationalTableModel();
    }
    visitsModel->setTable("visits");
    visitsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    visitsModel->setRelation(2, QSqlRelation("patients", "id", "name"));
    visitsModel->setRelation(3, QSqlRelation("doctors", "id", "name"));

    visitsModel->select();

    visitsModel->setHeaderData(1, Qt::Horizontal, tr("Дата"));
    visitsModel->setHeaderData(2, Qt::Horizontal, tr("Пациент"));
    visitsModel->setHeaderData(3, Qt::Horizontal, tr("Врач"));
    visitsModel->setHeaderData(4, Qt::Horizontal, tr("Диагноз"));
    visitsModel->setHeaderData(5, Qt::Horizontal, tr("Повторный"));
    visitsModel->setHeaderData(6, Qt::Horizontal, tr("Цена"));

    ui->tableView_visits->setModel(visitsModel);
    ui->tableView_visits->setColumnHidden(0, true);
    ui->tableView_visits->resizeColumnsToContents();
}

// Actions
void MainWindow::actionOpenFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Database"),
                                                    QDir::homePath(),
                                                    tr("MariaDB files (*.mwb)"));

    QMessageBox::information(this, "Open database", fileName);
}

void MainWindow::actionAbout() {
    QMessageBox::about(this,
                       "О Hospital Finance Tracing",
                       "<p><b>Hospital Finance Tracing</b> - программа для сбора финансовой статистики поликлиники</p>"
                       "<p>GitHub: <a href='https://github.com/MM-Collaboration/Hospital-Finance-Tracing'>https://github.com/MM-Collaboration/Hospital-Finance-Tracing</a></p>");
}

void MainWindow::on_btn_add_patient_clicked()
{
    qDebug() << " ui->dateEdit_yearOfBirthPatient->dateTime().toString(dd/MM/yy))" <<  ui->dateEdit_yearOfBirthPatient->dateTime().toString("dd/MM/yyyy");
    QSqlQuery query;
    query.prepare("INSERT INTO patients (name, date_of_birth, phone_number)"
                  "VALUES (:name, :date_of_birth, :phone_number)");
    query.bindValue(":name", ui->lineEdit_fullNamePatient->text());
    query.bindValue(":date_of_birth", ui->dateEdit_yearOfBirthPatient->dateTime().toString("yyyy"));
    query.bindValue(":phone_number", ui->lineEdit_phoneNumberPatient->text());
    query.exec();

    ui->lineEdit_fullNamePatient->clear();
    ui->dateEdit_yearOfBirthPatient->clear();
    ui->lineEdit_phoneNumberPatient->clear();

    reloadTablePatients();

    patientsModel->select();
}

void MainWindow::on_btn_edit_patient_clicked()
{

}

void MainWindow::on_btn_add_doctor_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO doctors (name, specialization, qualification) "
                  "VALUES (:name, :specialization, :qualification)");
    query.bindValue(":name", ui->lineEdit_fullNameDoctor->text());
    query.bindValue(":specialization", ui->comboBox_doctorSpecialization->currentText());
    query.bindValue(":qualification", ui->comboBox_doctorQualification->currentText());
    query.exec();
    ui->lineEdit_fullNameDoctor->clear();
    reloadTableDoctors();

    doctorsModel->select();

}

void MainWindow::activatePatientAddPushButton() {
    int phoneNumberLength = ui->lineEdit_phoneNumberPatient->text().length();
    if (!ui->lineEdit_fullNamePatient->text().isEmpty() && (!ui->lineEdit_phoneNumberPatient->text().isEmpty() && ((ui->lineEdit_phoneNumberPatient->text().split("")[1] == "+") ? (phoneNumberLength >= 12) : (phoneNumberLength >= 11)))) {
        ui->btn_add_patient->setEnabled(true);
    } else if (ui->btn_add_patient->isEnabled()) {
        ui->btn_add_patient->setEnabled(false);
    }
}

void MainWindow::activateVisitAddPushButton() {
    if (!ui->lineEdit_visitDiagnosis->text().isEmpty()) {
        ui->btn_add_appointment->setEnabled(true);
    } else if (ui->btn_add_appointment->isEnabled()) {
        ui->btn_add_appointment->setEnabled(false);
    }
}

void MainWindow::on_lineEdit_visitDiagnosis_textChanged(const QString &arg1)
{
    activateVisitAddPushButton();
}

void MainWindow::on_lineEdit_fullNameDoctor_textChanged()
{
    if (ui->lineEdit_fullNameDoctor->text().isEmpty()) {
        ui->btn_add_doctor->setEnabled(false);
    } else if (!ui->btn_add_doctor->isEnabled()) {
        ui->btn_add_doctor->setEnabled(true);
    }
}

void MainWindow::on_lineEdit_fullNamePatient_textChanged()
{
    activatePatientAddPushButton();
}

void MainWindow::on_lineEdit_phoneNumberPatient_textChanged(const QString &arg1)
{
    activatePatientAddPushButton();
}

void MainWindow::on_btn_add_appointment_clicked()
{
    // get patient id
    QSqlQuery patientIdQuery = QSqlQuery();
    patientIdQuery.prepare("SELECT id FROM doctors WHERE name=:patient_name");
    patientIdQuery.bindValue(":patient_name",  ui->comboBox_statDoctor->currentText());
    patientIdQuery.exec();
    int patient_id{}; //doctorIdQuery.boundValue(0).toInt() + 1;
    while (patientIdQuery.next()) {
        patient_id= patientIdQuery.value(0).toInt();
    }

    // get doctor id
    QSqlQuery doctorIdQuery = QSqlQuery();
    doctorIdQuery.prepare("SELECT id FROM doctors WHERE name=:doctor_name");
    doctorIdQuery.bindValue(":doctor_name",  ui->comboBox_vistDoctor->currentText());
    doctorIdQuery.exec();
    int doctor_id{};
    while (doctorIdQuery.next()) {
        doctor_id = doctorIdQuery.value(0).toInt();
    }

    // insert data into visits
    QSqlQuery query;
    query.prepare("INSERT INTO visits (date, patients_id, doctors_id, diagnosis, repeated_visit, price) "
                  "VALUES (:date, :patients_id, :doctors_id, :diagnosis, :repeated_visit, :price)");
    query.bindValue(":date",  ui->calendarWidget_visit->selectedDate().toString("dd/MM/yy"));
    query.bindValue(":patients_id", patient_id);
    query.bindValue(":doctors_id", doctor_id);
    query.bindValue(":diagnosis", ui->lineEdit_visitDiagnosis->text());
    query.bindValue(":repeated_visit", ui->checkBox_repeatedVisit->isChecked());
    query.bindValue(":price", ui->doubleSpinBox_visitPrice->value());
    query.exec();

    ui->lineEdit_fullNameDoctor->clear();
    reloadTableVisits();

    doctorsModel->select();
}

void MainWindow::on_tableView_patients_clicked(const QModelIndex &index)
{
    qDebug() << "Patient current row: " << index.row();
    qDebug() << "Patient current data: " << index.sibling(index.row(), 1).data().toString();
    ui->lineEdit_fullNamePatient->setText(index.sibling(index.row(), 1).data().toString());
//    ui->dateEdit_yearOfBirthPatient->setDate(index.sibling(index.row(), 2).data().toDate());
//    qDebug() << "index.sibling(index.row(), 1).data().toDate()): " << QString("12-12-" + index.sibling(index.row(), 2).data().toString());
    QString phone_number = index.sibling(index.row(), 3).data().toString();
    if (phone_number != QString("0")) {
        ui->lineEdit_phoneNumberPatient->setText(phone_number);
    } else {
        ui->lineEdit_phoneNumberPatient->setText("");
    }
}

void MainWindow::on_tableView_doctors_clicked(const QModelIndex &index)
{
    ui->lineEdit_fullNameDoctor->setText(index.sibling(index.row(), 1).data().toString());

    int specialization_index = ui->comboBox_doctorSpecialization->findText(index.sibling(index.row(), 2).data().toString());
    if (specialization_index != -1) { // -1 for not found
        ui->comboBox_doctorSpecialization->setCurrentIndex(specialization_index );
    }

    int qualification_index = ui->comboBox_doctorQualification->findText(index.sibling(index.row(), 2).data().toString());
    if (qualification_index != -1) { // -1 for not found
        ui->comboBox_doctorSpecialization->setCurrentIndex(qualification_index);
    }

}

void MainWindow::on_tableView_visits_clicked(const QModelIndex &index)
{
    int patient_index = ui->comboBox_vistPatient->findText(index.sibling(index.row(), 2).data().toString());
    if (patient_index != -1) { // -1 for not found
        ui->comboBox_vistPatient->setCurrentIndex(patient_index);
    }

    int doctor_index = ui->comboBox_vistDoctor->findText(index.sibling(index.row(), 3).data().toString());
    if (doctor_index != -1) { // -1 for not found
        ui->comboBox_vistDoctor->setCurrentIndex(doctor_index);
    }

    bool repeated_visit_flag = index.sibling(index.row(), 5).data().toBool();
    qDebug() << "repeated_visit_flag: " << repeated_visit_flag;
    ui->checkBox_repeatedVisit->setChecked(repeated_visit_flag);

    ui->doubleSpinBox_visitPrice->setValue(index.sibling(index.row(), 6).data().toDouble());
}


void MainWindow::on_pushButton_statUpdate_clicked()
{
    updateStat();
    statListModel = new QStringListModel(this);

    QStringList List;

    QSqlQuery doctorIdQuery = QSqlQuery();
    doctorIdQuery.prepare("SELECT id FROM doctors WHERE name=:doctor_name");
    doctorIdQuery.bindValue(":doctor_name",  ui->comboBox_statDoctor->currentText());
    doctorIdQuery.exec();
    int doctor_id{};
    while (doctorIdQuery.next()) {
        doctor_id = doctorIdQuery.value(0).toInt();
        qDebug() << "===========Doctor id: " << doctor_id;
    }
    qDebug() << "Doctor id: " << doctor_id;
    qDebug() << "comboBox_statDoctor->currentText: " <<  ui->comboBox_statDoctor->currentText();

    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT price FROM visits WHERE doctors_id=:doctor_id");
    query.bindValue(":doctor_id", doctor_id);
    query.exec();
    while (query.next()) {
        QString price = query.value(0).toString();
        qDebug() << "Doctor price: " << price;
        List.append(price);

    }
    qDebug() << "List: " << List;

    // Populate our model
    statListModel->setStringList(List);

    ui->listView_statAll->setModel(statListModel);
//    QModelIndex modelIndex;
//    statModel->insertRow(*statModelIndex, modelIndex);
//    statModelIndex++;
//    ui->tableView_statAll->setModel(statModel);
//    ui->tableView_statAll
}

void MainWindow::updateStat() {
    // set statPatients combobox items
    QSqlQuery query("SELECT name FROM doctors");
    while (query.next()) {
        QString name = query.value(0).toString();
        qDebug() << "Doctors name: " << name;
        ui->comboBox_statDoctor->addItem(name);
    }
}


