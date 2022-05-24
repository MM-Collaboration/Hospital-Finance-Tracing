#include "mainwindow.h"
#include "statchart.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    doctorsModel = nullptr;
    patientsModel = nullptr;
    visitsModel = nullptr;
    m_doctorDonatStatChart = nullptr;
    m_doctorBarStatChart = nullptr;
    m_doctorLineStatChart = nullptr;
    m_patientDonatStatChart = nullptr;
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
    ui->lineEdit_snils->setValidator(new QRegExpValidator(QRegExp("\\d{11}"), ui->lineEdit_snils));

    // restict calendar widget
    ui->calendarWidget_visit->setMinimumDate((new QDate)->currentDate());

    // Connect actions
    connect(ui->action_openFile, &QAction::triggered, this, &MainWindow::actionOpenFile);
    // Help menu
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::actionAbout);
    connect(ui->action_aboutQt, &QAction::triggered, this, QApplication::aboutQt);

    reloadTableDoctors();
    reloadTablePatients();

    reloadTableVisits();
    loadDoctorsSpecializationComboBox();
    loadDoctorsQualificationComboBox();

    updateStatDoctorsCheckBox();
    updateStatPatientsCheckBox();
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

void MainWindow::loadDoctorsSpecializationComboBox() {
    // set doctors specialization in combobox
    QSqlQuery query("SELECT specialization FROM doctors_specializations");
    while (ui->comboBox_doctorSpecialization->count() != 0) { // claer comboBox
        ui->comboBox_doctorSpecialization->removeItem(0);
    }
    while (query.next()) {
        QString specialization = query.value(0).toString();
        ui->comboBox_doctorSpecialization->addItem(specialization);
    }
}

void MainWindow::loadDoctorsQualificationComboBox() {
    // set doctors qualifiation in combobox
    QSqlQuery query("SELECT qualification FROM doctors_qualifications");
    while (ui->comboBox_doctorQualification->count() != 0) { // claer comboBox
        ui->comboBox_doctorQualification->removeItem(0);
    }
    while (query.next()) {
        QString qualification = query.value(0).toString();
        ui->comboBox_doctorQualification->addItem(qualification);
    }
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
    patientsModel->setHeaderData(4, Qt::Horizontal, tr("СНИЛС"));

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
    QSqlQuery query;
    query.prepare("INSERT INTO patients (name, date_of_birth, phone_number, snils)"
                  "VALUES (:name, :date_of_birth, :phone_number, :snils)");
    query.bindValue(":name", ui->lineEdit_fullNamePatient->text());
    query.bindValue(":date_of_birth", ui->dateEdit_yearOfBirthPatient->dateTime().toString("yyyy"));
    query.bindValue(":phone_number", ui->lineEdit_phoneNumberPatient->text());
    query.bindValue(":snils", ui->lineEdit_snils->text());
    query.exec();

    ui->lineEdit_fullNamePatient->clear();
    ui->lineEdit_phoneNumberPatient->clear();

    reloadTablePatients();

    patientsModel->select();
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
    bool validPhoneNumber = (((ui->lineEdit_phoneNumberPatient->text().split("")[1] == "+") ? (phoneNumberLength >= 12) : (phoneNumberLength >= 11)));
    bool validFullName = !ui->lineEdit_fullNamePatient->text().isEmpty();
    bool validSnilsNumber = (!ui->lineEdit_snils->text().isEmpty() && ui->lineEdit_snils->text().length() == 11);
    qDebug() << "validFullName: " << validFullName;
    qDebug() << "valudSnilsNumber: " << validSnilsNumber;
    qDebug() << "validPhoneNumber: " << validPhoneNumber;

    if (validFullName && validPhoneNumber && validSnilsNumber) {
        ui->btn_add_patient->setEnabled(true);
        // clear all
        highlightWidget(ui->lineEdit_fullNamePatient, false);
        highlightWidget(ui->lineEdit_phoneNumberPatient, false);
        highlightWidget(ui->lineEdit_snils, false);
    } else {
        if (ui->btn_add_patient->isEnabled()) {
            ui->btn_add_patient->setEnabled(false);
        }

        // highlight if not valid
        if (!validFullName)
            highlightWidget(ui->lineEdit_fullNamePatient, true);
        else
            highlightWidget(ui->lineEdit_fullNamePatient, false);

        if (!validPhoneNumber)
            highlightWidget(ui->lineEdit_phoneNumberPatient, true);
        else
            highlightWidget(ui->lineEdit_phoneNumberPatient, false);

        if (!validSnilsNumber)
            highlightWidget(ui->lineEdit_snils, true);
        else
            highlightWidget(ui->lineEdit_snils, false);

        // clear if all empty
        if (ui->lineEdit_fullNamePatient->text().isEmpty() &&
            ui->lineEdit_phoneNumberPatient->text().isEmpty() &&
            ui->lineEdit_snils->text().isEmpty())
        {
            highlightWidget(ui->lineEdit_fullNamePatient, false);
            highlightWidget(ui->lineEdit_phoneNumberPatient, false);
            highlightWidget(ui->lineEdit_snils, false);
        }
    }

}

void MainWindow::highlightWidget(QWidget *widget, bool flag) {
        if (flag) {
            widget->setStyleSheet("background-color: rgb(255, 158, 160);");
        } else {
            widget->setStyleSheet("");
        }
}

void MainWindow::activateVisitAddPushButton() {
    bool validDianosis = (!ui->lineEdit_visitDiagnosis->text().isEmpty());
    bool validPatientName = false;
    if (ui->comboBox_vistPatient->findText(ui->comboBox_vistPatient->currentText()) != -1) {
        validPatientName = true;
    }
    bool validDoctorName = false;
    if (ui->comboBox_vistDoctor->findText(ui->comboBox_vistDoctor->currentText()) != -1) {
        validDoctorName = true;
    }
    if (validDianosis && validDoctorName && validPatientName) {
        ui->btn_add_appointment->setEnabled(true);
        // clear all
        highlightWidget(ui->comboBox_vistPatient, false);
        highlightWidget(ui->comboBox_vistDoctor, false);
        highlightWidget(ui->lineEdit_visitDiagnosis, false);
    } else {
        if (ui->btn_add_appointment->isEnabled()) {
            ui->btn_add_appointment->setEnabled(false);
        }

        // highlight if not valid
        if (!validPatientName)
            highlightWidget(ui->comboBox_vistPatient, true);
        else
            highlightWidget(ui->comboBox_vistPatient, false);

        if (!validDoctorName)
            highlightWidget(ui->comboBox_vistDoctor, true);
        else
            highlightWidget(ui->comboBox_vistDoctor, false);

        if (!validDianosis)
            highlightWidget(ui->lineEdit_visitDiagnosis, true);
        else
            highlightWidget(ui->lineEdit_visitDiagnosis, false);

        // clear if all empty
//        if (ui->lineEdit_fullNamePatient->text().isEmpty() &&
//            ui->lineEdit_phoneNumberPatient->text().isEmpty() &&
//            ui->lineEdit_snils->text().isEmpty())
//        {
//            highlightWidget(ui->lineEdit_fullNamePatient, false);
//            highlightWidget(ui->lineEdit_phoneNumberPatient, false);
//            highlightWidget(ui->lineEdit_snils, false);
//        }
    }
   /*
    else {
        if (ui->btn_add_patient->isEnabled()) {
            ui->btn_add_patient->setEnabled(false);
        }

        // highlight if not valid
        ef (!validFullName)
            highlightWidget(ui->lineEdit_fullNamePatient, true);
        else
            highlightWidget(ui->lineEdit_fullNamePatient, false);

        if (!validPhoneNumber)
            highlightWidget(ui->lineEdit_phoneNumberPatient, true);
        else
            highlightWidget(ui->lineEdit_phoneNumberPatient, false);

        if (!validSnilsNumber)
            highlightWidget(ui->lineEdit_snils, true);
        else
            highlightWidget(ui->lineEdit_snils, false);

        // clear if all empty
        if (ui->lineEdit_fullNamePatient->text().isEmpty() &&
            ui->lineEdit_phoneNumberPatient->text().isEmpty() &&
            ui->lineEdit_snils->text().isEmpty())
        {
            highlightWidget(ui->lineEdit_fullNamePatient, false);
            highlightWidget(ui->lineEdit_phoneNumberPatient, false);
            highlightWidget(ui->lineEdit_snils, false);
        }
    }
    */
}

void MainWindow::on_lineEdit_visitDiagnosis_textChanged(const QString &arg1)
{
    activateVisitAddPushButton();
}

void MainWindow::activateDoctorAddPushButton()
{
    bool validDoctorName = !ui->lineEdit_fullNameDoctor->text().isEmpty();
    bool validQualification = false;
    if (ui->comboBox_doctorQualification->findText(ui->comboBox_doctorQualification->currentText()) != -1) {
        validQualification = true;
    }
    bool validSpecialization = false;
    if (ui->comboBox_doctorSpecialization->findText(ui->comboBox_doctorSpecialization->currentText()) != -1) {
        validSpecialization = true;
    }
    if (validDoctorName && validQualification && validSpecialization) {
        ui->btn_add_doctor->setEnabled(true);
        // clear all
        highlightWidget(ui->lineEdit_fullNameDoctor, false);
        highlightWidget(ui->comboBox_doctorQualification, false);
        highlightWidget(ui->comboBox_doctorSpecialization, false);
    } else {
        if (ui->btn_add_doctor->isEnabled()) {
            ui->btn_add_doctor->setEnabled(false);
        }

        // highlight if not valid
        if (!validDoctorName)
            highlightWidget(ui->lineEdit_fullNameDoctor, true);
        else
            highlightWidget(ui->lineEdit_fullNameDoctor, false);

        if (!validQualification)
            highlightWidget(ui->comboBox_doctorQualification, true);
        else
            highlightWidget(ui->comboBox_doctorQualification, false);

        if (!validSpecialization)
            highlightWidget(ui->comboBox_doctorSpecialization, true);
        else
            highlightWidget(ui->comboBox_doctorSpecialization, false);
/*
        // clear if all empty
        if (ui->lineEdit_fullNamePatient->text().isEmpty() &&
            ui->lineEdit_phoneNumberPatient->text().isEmpty() &&
            ui->lineEdit_snils->text().isEmpty())
        {
            highlightWidget(ui->lineEdit_fullNamePatient, false);
            highlightWidget(ui->lineEdit_phoneNumberPatient, false);
            highlightWidget(ui->lineEdit_snils, false);
        }
    }
     */
    }
}

void MainWindow::on_lineEdit_fullNameDoctor_textChanged()
{
    activateDoctorAddPushButton();
}

void MainWindow::on_lineEdit_phoneNumberPatient_textChanged(const QString &arg1)
{
    activatePatientAddPushButton();
}

void MainWindow::on_btn_add_appointment_clicked()
{
    // get patient id
    QSqlQuery patientIdQuery = QSqlQuery();
    patientIdQuery.prepare("SELECT id FROM patients WHERE name=:patient_name");
    patientIdQuery.bindValue(":patient_name",  ui->comboBox_vistPatient->currentText());
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
    query.prepare(" INSERT INTO visits (date, patients_id, doctors_id, diagnosis, repeated_visit, price)"
                  "VALUES (:date, :patients_id, :doctors_id, :diagnosis, :repeated_visit, :price)");
    query.bindValue(":date",  ui->calendarWidget_visit->selectedDate().toString("yy/MM/dd"));
    query.bindValue(":patients_id", patient_id);
    query.bindValue(":doctors_id", doctor_id);
    query.bindValue(":diagnosis", ui->lineEdit_visitDiagnosis->text());
    query.bindValue(":repeated_visit", ui->checkBox_repeatedVisit->isChecked() == true ? 1 : 0);
    query.bindValue(":price", ui->doubleSpinBox_visitPrice->value());
    query.exec();

    ui->lineEdit_fullNameDoctor->clear();
    ui->lineEdit_visitDiagnosis->clear();
    reloadTableVisits();

    doctorsModel->select();
}

void MainWindow::on_tableView_patients_clicked(const QModelIndex &index)
{
    ui->lineEdit_fullNamePatient->setText(index.sibling(index.row(), 1).data().toString());
//    ui->dateEdit_yearOfBirthPatient->setDate(index.sibling(index.row(), 2).data().toDate());
//    qDebug() << "index.sibling(index.row(), 1).data().toDate()): " << QString("12-12-" + index.sibling(index.row(), 2).data().toString());
    ui->lineEdit_snils->setText(index.sibling(index.row(), 4).data().toString());

    QString phone_number = index.sibling(index.row(), 3).data().toString();
    QString snils_number = index.sibling(index.row(), 4).data().toString();
    if (phone_number != QString("0")) {
        ui->lineEdit_phoneNumberPatient->setText(phone_number);
        ui->lineEdit_snils->setText(snils_number);
    } else {
        ui->lineEdit_phoneNumberPatient->setText("");
        ui->lineEdit_snils->setText("");
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
    ui->checkBox_repeatedVisit->setChecked(repeated_visit_flag);

    ui->doubleSpinBox_visitPrice->setValue(index.sibling(index.row(), 6).data().toDouble());
}

void MainWindow::updateStatDoctorsCheckBox() {
    // set statPatients combobox items

    QString currentName = ui->comboBox_statDoctor->currentText();

    while (ui->comboBox_statDoctor->count()) {
        ui->comboBox_statDoctor->removeItem(0);
    }

    QSqlQuery query("SELECT name FROM doctors");
    while (query.next()) {
        QString name = query.value(0).toString();
        ui->comboBox_statDoctor->addItem(name);
    }

    // restore selected name
    int index = ui->comboBox_statDoctor->findText(currentName);
    if (index != -1) { // -1 not found
        ui->comboBox_statDoctor->setCurrentIndex(index);
    }
}

void MainWindow::updateStatPatientsCheckBox()
{
    // set statPatients combobox items

    QString currentName = ui->comboBox_statPatient->currentText();

    while (ui->comboBox_statPatient->count()) {
        ui->comboBox_statPatient->removeItem(0);
    }

    QSqlQuery query("SELECT name FROM patients");
    while (query.next()) {
        QString name = query.value(0).toString();
        ui->comboBox_statPatient->addItem(name);
    }

    // restore selected name
    int index = ui->comboBox_statPatient->findText(currentName);
    if (index != -1) { // -1 not found
        ui->comboBox_statPatient->setCurrentIndex(index);
    }
}

void MainWindow::updateDoctorStat()
{
    QVector<int> patients_id;
    QVector<QString> patientsName;
    QVector<double> prices;
    QVector<QDate> dates;
    QVector<bool> repeated_visits;

    // get doctor id
    int doctor_id{};
    QSqlQuery doctorIdQuery = QSqlQuery();
    doctorIdQuery.prepare("SELECT id FROM doctors WHERE name=:doctor_name");
    doctorIdQuery.bindValue(":doctor_name",  ui->comboBox_statDoctor->currentText());
    doctorIdQuery.exec();
    while (doctorIdQuery.next()) {
        doctor_id = doctorIdQuery.value(0).toInt();
    }

    // get price and patients price, patients_id, date, repeated_visit
    QSqlQuery query = QSqlQuery();
    query.prepare("SELECT price, patients_id, date, repeated_visit FROM visits WHERE doctors_id=:doctor_id");
    query.bindValue(":doctor_id", doctor_id);
    if (query.exec()) {
        while (query.next()) {
            patients_id.append(query.value(1).toInt());
            prices.append(query.value(0).toInt());
            dates.append(query.value(2).toDate());
            repeated_visits.append(query.value(3).toBool());
        }
    } else {
        qDebug() << "SELECT price FROM visits WHERE doctors_id=:doctor_id: " << "query not exec()";
    }

    //  get paitent name
    for (int patient_id: patients_id) {
        QSqlQuery patientQuery = QSqlQuery();
        query.prepare("SELECT name FROM patients WHERE id=:patient_id");
        query.bindValue(":patient_id", patient_id);
        if (query.exec()) {
            while(query.next()) {
                patientsName.append(query.value(0).toString());
            }
        } else {
            qDebug() << "SELECT name FROM patients WHERE id=:patient_id: " << "query not exec()";
        }
    }

    // fill doctorStat table
    QStringList doctorStatHorizontalHeaderLabels;
    doctorStatHorizontalHeaderLabels.append("Дата");
    doctorStatHorizontalHeaderLabels.append("Пациент");
    doctorStatHorizontalHeaderLabels.append("Цена");
    doctorStatHorizontalHeaderLabels.append("Повторный приём");
    ui->tableWidget_doctorStat->setColumnCount(doctorStatHorizontalHeaderLabels.count());
    ui->tableWidget_doctorStat->setRowCount(patientsName.count());
    ui->tableWidget_doctorStat->setHorizontalHeaderLabels(doctorStatHorizontalHeaderLabels);
    for (int row = 0; row < patientsName.count(); row++) {
        ui->tableWidget_doctorStat->setItem(row, 0, new QTableWidgetItem(dates[row].toString("yy/MM/dd")));
        ui->tableWidget_doctorStat->setItem(row, 1, new QTableWidgetItem(patientsName[row]));
        ui->tableWidget_doctorStat->setItem(row, 2, new QTableWidgetItem(QString().number(prices[row])));

        QString repeatedVisitMarkIconPath;
        QString repeatedVisitText;
        if (repeated_visits[row]) {
            repeatedVisitMarkIconPath = ":/icons/checkMarkTrue";
            repeatedVisitText = "Да";
        } else {
            repeatedVisitMarkIconPath = ":/icons/checkMarkFalse";
            repeatedVisitText = "Нет";
        }
        ui->tableWidget_doctorStat->setItem(row, 3, new QTableWidgetItem(QIcon(repeatedVisitMarkIconPath), repeatedVisitText));
    }
    ui->tableWidget_doctorStat->resizeColumnsToContents();

    // form doctor stat review
    QString doctorFullName = ui->comboBox_statDoctor->currentText();
    QString pageLabel = QStringLiteral("Приёмы %1").arg(doctorFullName);
    ui->label_doctorVisits->setText(pageLabel);
    double paidTotal = 0;
    for (double price: prices) paidTotal += price;
    QString statReviewStr = QStringLiteral("Врач: %1\n"
                                           "Количество приёмов: %2\n"
                                           "Общая стоимость приёмов: %3").arg(doctorFullName).arg(patientsName.count()).arg(paidTotal);
    ui->textBrowser_statReview->setText(statReviewStr);

    // fill donat chart
    QPieSeries *series = new QPieSeries;
//    series->setName("testName");
//    QPieSlice *slice = series->append(patientsName[0], prices[0]);
//    slice->setExploded();
    for (int i = 0; i < dates.count(); i ++) {
        series->append(patientsName[i], prices[i]);
    }

    if (m_doctorDonatStatChart != nullptr) {
        delete m_doctorDonatStatChart;
    }
    m_doctorDonatStatChart = new StatChart(this, &pageLabel);
    m_doctorDonatStatChart->loadSeries(series);

    // fill bar chart
    QBarSeries *barSeries = new QBarSeries();
    for (int i = 0; i < dates.count(); i++) {
        QBarSet *set = new QBarSet(patientsName[i]);
        *set << prices[i];
        barSeries->append(set);
    }

    if (m_doctorBarStatChart != nullptr) {
        delete m_doctorBarStatChart;
    }
    m_doctorBarStatChart = new StatChart(this, &pageLabel);
    m_doctorBarStatChart ->loadSeries(barSeries);

    // fill line chart
    QLineSeries *lineSeries = new QLineSeries();

    // get min and max date
    QDate maxDate;
    QSqlQuery maxDateQuery = QSqlQuery();
    maxDateQuery .prepare("SELECT date FROM visits WHERE doctors_id=:doctor_id ORDER BY date");
    maxDateQuery .bindValue(":doctor_id",  doctor_id);
    maxDateQuery.exec();
    while(maxDateQuery.next()) {
        maxDate = maxDateQuery.value(0).toDate();
    }

    QDate minDate;
    QSqlQuery minDateQuery = QSqlQuery();
    minDateQuery.prepare("SELECT date FROM visits WHERE doctors_id=:doctor_id ORDER BY date DESC");
    minDateQuery.bindValue(":doctor_id",  doctor_id);

    if (minDateQuery.exec()) {
        while(minDateQuery.next()) {
            minDate = minDateQuery.value(0).toDate();
        }
    } else {
        qDebug() << "SELECT date FROM visits WHERE doctors_id=:doctor_id ORDER BY date DESC: " << "falid to exec";
    }

    if (!maxDate.isNull()) {
        int daysRange = minDate.daysTo(maxDate);
        double step = daysRange / dates.count();
        double currentPosition = 0;
        for (int i = 0; i < dates.count(); i++) {
            *lineSeries << QPointF(currentPosition, prices[i]);
            currentPosition += step;
        }

    }

    if (m_doctorLineStatChart != nullptr) {
        delete m_doctorLineStatChart ;
    }
    m_doctorLineStatChart = new StatChart(this, &pageLabel);
    m_doctorLineStatChart ->loadSeries(lineSeries);

    // display charts
    ui->verticalLayout_doctorPieChart->addWidget(m_doctorDonatStatChart);
    ui->verticalLayout_doctorBarsChart->addWidget(m_doctorBarStatChart);
    ui->verticalLayout_doctorLineChart->addWidget(m_doctorLineStatChart);
}

void MainWindow::updateLatestVisitsStat()
{
    QVector<QDate> dates;
    QVector<int> patients_id;
    QVector<int> doctors_id;
    QVector<double> prices;
    QVector<bool> repeated_visits;
    QVector<QString> patientsNames;
    QVector<QString> doctorsNames;

    // get patient date, patients_id, doctors_id, price, repeated_visit
    QSqlQuery visitQuery = QSqlQuery();
    visitQuery.prepare("SELECT date, patients_id, doctors_id, price, repeated_visit  FROM visits t1 WHERE date = (SELECT max(date) from visits WHERE patients_id = t1.patients_id);");
    visitQuery.bindValue(":doctor_name",  ui->comboBox_statDoctor->currentText());
    visitQuery.exec();
    while (visitQuery.next()) {
        dates.append(visitQuery.value(0).toDate());
        patients_id.append(visitQuery.value(1).toInt());
        doctors_id.append(visitQuery.value(2).toInt());
        prices.append(visitQuery.value(3).toDouble());
        repeated_visits.append(visitQuery.value(4).toBool());
    }

    //  get paitents name
    for (int patient_id: patients_id) {
        QSqlQuery patientQuery = QSqlQuery();
        patientQuery .prepare("SELECT name FROM patients WHERE id=:patient_id");
        patientQuery.bindValue(":patient_id", patient_id);
        if (patientQuery.exec()) {
            while(patientQuery.next()) {
                patientsNames.append(patientQuery.value(0).toString());
            }
        } else {
            qDebug() << "SELECT name FROM patients WHERE id=:patient_id: " << "patientQuery not exec()";
        }
    }

    //  get doctors name
    for (int doctor_id: doctors_id) {
        QSqlQuery doctorQuery = QSqlQuery();
        doctorQuery .prepare("SELECT name FROM doctors WHERE id=:doctor_id");
        doctorQuery.bindValue(":doctor_id", doctor_id);
        if (doctorQuery.exec()) {
            while(doctorQuery.next()) {
                doctorsNames.append(doctorQuery.value(0).toString());
            }
        } else {
            qDebug() << "SELECT name FROM doctors WHERE id=:doctor_id: " << "doctorQuery not exec()";
        }
    }

    // fill doctorStat table
    QStringList patientStatHorizontalHeaderLabels;
    patientStatHorizontalHeaderLabels.append("Дата");
    patientStatHorizontalHeaderLabels.append("Пациент");
    patientStatHorizontalHeaderLabels.append("Врач");
    patientStatHorizontalHeaderLabels.append("Цена");
    patientStatHorizontalHeaderLabels.append("Повторный приём");
    ui->tableWidget_patientsStat->setColumnCount(patientStatHorizontalHeaderLabels.count());
    ui->tableWidget_patientsStat->setRowCount(patientsNames.count());
    ui->tableWidget_patientsStat->setHorizontalHeaderLabels(patientStatHorizontalHeaderLabels);

    for (int row = 0; row < patientsNames.count(); row++) {
        ui->tableWidget_patientsStat->setItem(row, 0, new QTableWidgetItem(dates[row].toString("yy/MM/dd")));
        ui->tableWidget_patientsStat->setItem(row, 1, new QTableWidgetItem(patientsNames[row]));
        ui->tableWidget_patientsStat->setItem(row, 2, new QTableWidgetItem(doctorsNames[row]));
        ui->tableWidget_patientsStat->setItem(row, 3, new QTableWidgetItem(QString().number(prices[row])));

        QString repeatedVisitMarkIconPath;
        QString repeatedVisitText;
        if (repeated_visits[row]) {
            repeatedVisitMarkIconPath = ":/icons/checkMarkTrue";
            repeatedVisitText = "Да";
        } else {
            repeatedVisitMarkIconPath = ":/icons/checkMarkFalse";
            repeatedVisitText = "Нет";
        }
        ui->tableWidget_patientsStat->setItem(row, 4, new QTableWidgetItem(QIcon(repeatedVisitMarkIconPath), repeatedVisitText));
    }

    ui->tableWidget_patientsStat->resizeColumnsToContents();
}

void MainWindow::updatePatientVisitsStat()
{
    QVector<QDate> dates;
    QVector<int> doctors_id;
    QVector<double> prices;
    QVector<bool> repeated_visits;
    QVector<QString> doctorsNames;

    int patient_id = 0;
    QSqlQuery patientQuery = QSqlQuery();
    patientQuery.prepare("SELECT id FROM patients WHERE name=:patient_name");
    patientQuery.bindValue(":patient_name",  ui->comboBox_statPatient->currentText());
    if (patientQuery.exec()) {
        while (patientQuery.next()) {
            patient_id = patientQuery.value(0).toInt();
        }
    } else {
        qDebug() << "select id from patients where name=:patient_name: " << "failed to exec";
    }

    // get patient date, doctors_id, price, repeated_visit
    QSqlQuery visitQuery = QSqlQuery();
    visitQuery.prepare("SELECT date, doctors_id, price, repeated_visit FROM visits WHERE patients_id=:patient_id");
    visitQuery.bindValue(":patient_id", patient_id);
    if (visitQuery.exec()) {
        while (visitQuery.next()) {
            dates.append(visitQuery.value(0).toDate());
            doctors_id.append(visitQuery.value(1).toInt());
            prices.append(visitQuery.value(2).toDouble());
            repeated_visits.append(visitQuery.value(3).toBool());
        }
    } else {
        qDebug() << "select id from patients where name=:patient_name: " << "failed to exec";
    }

    //  get doctors name
    for (int doctor_id: doctors_id) {
        QSqlQuery doctorQuery = QSqlQuery();
        doctorQuery.prepare("SELECT name FROM doctors WHERE id=:doctor_id");
        doctorQuery.bindValue(":doctor_id", doctor_id);
        if (doctorQuery.exec()) {
            while(doctorQuery.next()) {
                doctorsNames.append(doctorQuery.value(0).toString());
            }
        } else {
            qDebug() << "SELECT name FROM doctors WHERE id=:doctor_id: " << "doctorQuery not exec()";
        }
    }

    // fill doctorStat table
    QStringList patientStatHorizontalHeaderLabels;
    patientStatHorizontalHeaderLabels.append("Дата");
    patientStatHorizontalHeaderLabels.append("Врач");
    patientStatHorizontalHeaderLabels.append("Цена");
    patientStatHorizontalHeaderLabels.append("Повторный приём");
    ui->tableWidget_patientVisitStat->setColumnCount(patientStatHorizontalHeaderLabels.count());
    ui->tableWidget_patientVisitStat->setRowCount(doctorsNames.count());
    ui->tableWidget_patientVisitStat->setHorizontalHeaderLabels(patientStatHorizontalHeaderLabels);

    for (int row = 0; row < doctorsNames.count(); row++) {
        ui->tableWidget_patientVisitStat->setItem(row, 0, new QTableWidgetItem(dates[row].toString("yy/MM/dd")));
        ui->tableWidget_patientVisitStat->setItem(row, 1, new QTableWidgetItem(doctorsNames[row]));
        ui->tableWidget_patientVisitStat->setItem(row, 2, new QTableWidgetItem(QString().number(prices[row])));

        QString repeatedVisitMarkIconPath;
        QString repeatedVisitText;
        if (repeated_visits[row]) {
            repeatedVisitMarkIconPath = ":/icons/checkMarkTrue";
            repeatedVisitText = "Да";
        } else {
            repeatedVisitMarkIconPath = ":/icons/checkMarkFalse";
            repeatedVisitText = "Нет";
        }
        ui->tableWidget_patientVisitStat->setItem(row, 3, new QTableWidgetItem(QIcon(repeatedVisitMarkIconPath), repeatedVisitText));
    }

    ui->tableWidget_patientVisitStat->resizeColumnsToContents();

    // form doctor stat review
    QString patientFullName = ui->comboBox_statPatient->currentText();
    QString pageLabel = QStringLiteral("Обращения %1").arg(patientFullName);
    ui->label_patientVisit->setText(pageLabel);
    double paidTotal = 0;
    for (double price: prices) paidTotal += price;
    QString patientReviewStr= QStringLiteral("Пациент: %1\n"
                                           "Количество приёмов: %2\n"
                                           "Общая стоимость приёмов: %3").arg(patientFullName).arg(doctorsNames.count()).arg(paidTotal);
    ui->textBrowser_patientReview->setText(patientReviewStr);


    // fill donat chart
    QPieSeries *series = new QPieSeries;
    for (int i = 0; i < dates.count(); i ++) {
        series->append(doctorsNames[i], prices[i]);
    }

    if (m_patientDonatStatChart != nullptr) {
        delete m_patientDonatStatChart ;
    }
    m_patientDonatStatChart = new StatChart(this, &pageLabel);
    m_patientDonatStatChart->loadSeries(series);

    ui->verticalLayout_patientsPieChart->addWidget(m_patientDonatStatChart);
}

void MainWindow::on_pushButton_statUpdate_clicked()
{
    updateStatDoctorsCheckBox();
    updateStatPatientsCheckBox();

    updateDoctorStat();
    updateLatestVisitsStat();
    updatePatientVisitsStat();

}

void MainWindow::on_lineEdit_snils_textChanged(const QString &arg1)
{
    activatePatientAddPushButton();
}


void MainWindow::on_comboBox_vistPatient_editTextChanged(const QString &arg1)
{
    activateVisitAddPushButton();
}


void MainWindow::on_comboBox_vistDoctor_editTextChanged(const QString &arg1)
{
    activateVisitAddPushButton();
}


void MainWindow::on_lineEdit_fullNamePatient_textChanged(const QString &arg1)
{
    activatePatientAddPushButton();
}


void MainWindow::on_comboBox_doctorSpecialization_currentTextChanged(const QString &arg1)
{
    activateDoctorAddPushButton();
}


void MainWindow::on_comboBox_doctorQualification_currentTextChanged(const QString &arg1)
{
    activateDoctorAddPushButton();
}

