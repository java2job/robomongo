#include "robomongo/gui/dialogs/AboutDialog.h"

#include <QDate>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QTextBrowser>
#include <QFile>
#include <Qsci/qsciglobal.h>

#include "robomongo/gui/GuiRegistry.h"
#include "robomongo/core/utils/QtUtils.h"

namespace
{    
    const QString description {
        "<h3>" PROJECT_NAME_TITLE " " PROJECT_VERSION "</h3>"
        "Shell-centric MongoDB management tool.<br/>"
        "<a href=\"https://" PROJECT_GITHUB_ISSUES "\">Submit</a> issues/proposals on GitHub.<br/>"
        "<br/>"

        "<a href=\"https://" PROJECT_DOMAIN "\">" PROJECT_DOMAIN "</a> <br/>"
        "Copyright 2014-" + QString::number(QDate::currentDate().year()) +
        " <a href= " PROJECT_COMPANYNAME_DOMAIN " >" PROJECT_COMPANYNAME "</a>. All rights reserved.<br/>"
        "<br/>"

        "The program is provided AS IS with NO WARRANTY OF ANY KIND, "
        "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A "
        "PARTICULAR PURPOSE.<br/>"
        "<br>"

        "<b>Dependencies: <br></b>"
        "Mongo-Shell " MongoDB_VERSION "<br>"
        "Qt " PROJECT_QT_VERSION "<br>"
        "OpenSSL " 	   OPENSSL_VERSION "<br>"
        "libssh2 " 	   LIBSSH2_VERSION "<br>"
        "QJson "   	   QJSON_VERSION "<br>"
        "QScintilla "  QSCINTILLA_VERSION_STR "<br>"
        "Google Test " GOOGLE_TEST_VERSION "<br>"
        "ESPRIMA "      ESPRIMA_VERSION "<br>"
        "<br>"

        "<b>Credits: <br/></b>"
        "Some icons are designed by Freepik <a href=http://www.flaticon.com>www.flaticon.com</a>"
        "<br/>"
    };        
}

namespace Robomongo
{
    AboutDialog::AboutDialog(QWidget *parent)
        : QDialog(parent)
    {
        setWindowTitle("About " PROJECT_NAME_TITLE);

        //// About tab
        auto aboutTab = new QWidget;
        aboutTab->setWindowIcon(GuiRegistry::instance().mainWindowIcon());
        aboutTab->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
        auto layout = new QGridLayout(this);
        layout->setSizeConstraint(QLayout::SetFixedSize);

        auto copyRightLabel = new QLabel(description);
        copyRightLabel->setWordWrap(true);
        copyRightLabel->setOpenExternalLinks(true);
        copyRightLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

        QIcon icon = GuiRegistry::instance().mainWindowIcon();
        QPixmap iconPixmap = icon.pixmap(128, 128);

        auto logoLabel = new QLabel;
        logoLabel->setPixmap(iconPixmap);
        layout->addWidget(logoLabel, 0, 0, 1, 1);
        layout->addWidget(copyRightLabel, 0, 1, 4, 4);
        aboutTab->setLayout(layout);

        //// License Agreement tab
        auto licenseTab = new QWidget;
        auto textBrowser = new QTextBrowser;
        textBrowser->setOpenExternalLinks(true);
        textBrowser->setOpenLinks(true);
        QFile file(":gnu_gpl3_license.html");
        if (file.open(QFile::ReadOnly | QFile::Text))
            textBrowser->setText(file.readAll());
        
        auto licenseTabLay = new QVBoxLayout;
        licenseTabLay->addWidget(textBrowser);
        licenseTab->setLayout(licenseTabLay);

        //// Button box
        auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
        QPushButton *closeButton = buttonBox->button(QDialogButtonBox::Close);
        buttonBox->addButton(closeButton, QDialogButtonBox::ButtonRole(QDialogButtonBox::RejectRole |
                                                                       QDialogButtonBox::AcceptRole));
        VERIFY(connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject())));

        //// Main layout
        auto tabWidget = new QTabWidget;
        tabWidget->addTab(aboutTab, "About");
        tabWidget->addTab(licenseTab, "License Agreement");

        auto mainLayout = new QVBoxLayout;
        mainLayout->addWidget(tabWidget);
        mainLayout->addWidget(buttonBox);
        setLayout(mainLayout);
    }
}
