/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - The Lightweight Desktop Environment
 * https://lxqt-project.org
 *
 * Copyright: 2011-12 Razor Team;  2012-2020 LXQt Project
 * Authors:
 *   Petr Vanek <petr@scribus.info>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "lxqtaboutdialog.h"
#include "ui_lxqtaboutdialog.h"
#include "lxqtaboutdialog_p.h"
#include "technicalinfo.h"
#include "translatorsinfo/translatorsinfo.h"

#include <QDebug>
#include <QDate>
#include <QClipboard>

AboutDialogPrivate::AboutDialogPrivate()
{
    setWindowIcon(QIcon::fromTheme(QString::fromStdString("help-about")));
    setupUi(this);

    QString css=QStringLiteral("<style TYPE='text/css'> "
                    "body { font-family: sans-serif;} "
                    ".name { font-size: 16pt; } "
                    "a { white-space: nowrap ;} "
                    "h2 { font-size: 10pt;} "
                    "li { line-height: 120%;} "
                    ".techInfoKey { white-space: nowrap ; margin: 0 20px 0 16px; } "
                "</style>")
            ;
    QIcon qicon = QIcon::fromTheme(QString::fromStdString("panther"));
    QPixmap pixmap = qicon.pixmap(50, QIcon::Normal, QIcon::On);
 //iconLabel->setFixedSize(30, 30);
    iconLabel->setScaledContents(true);
    iconLabel->setPixmap(pixmap);

    nameLabel->setText(css + titleText());

    aboutBrowser->setHtml(css + aboutText());
    aboutBrowser->viewport()->setAutoFillBackground(false);

    autorsBrowser->setHtml(css + authorsText());
    autorsBrowser->viewport()->setAutoFillBackground(false);

    // thanksBrowser->setHtml(css + thanksText());
    // thanksBrowser->viewport()->setAutoFillBackground(false);

    // translationsBrowser->setHtml(css + translationsText());
    // translationsBrowser->viewport()->setAutoFillBackground(false);

    // TechnicalInfo info;
    // techBrowser->setHtml(info.html());
    // techBrowser->viewport()->setAutoFillBackground(false);

    // connect(techCopyToClipboardButton, &QPushButton::clicked, this, &AboutDialogPrivate::copyToCliboardTechInfo);
    this->setAttribute(Qt::WA_DeleteOnClose);
    show();

}

QString AboutDialogPrivate::titleText() const
{
    return QStringLiteral("<div class=name>%1</div><div class=ver>%2</div>").arg(QStringLiteral("PantherX OS"),
                tr("Version: %1").arg(QStringLiteral("Beta 1")));

}

QString AboutDialogPrivate::aboutText() const
{
    return QStringLiteral(
        "<p>%1</p>"
        "<p>%2</p>"
        "<p>%3</p>"
        "<p>%4</p>"        
        )
        .arg(
            tr(" A modern, Unix-like computer operating system with a light-weight desktop environment\n, a set of highly polished,homegrown applications, and access to thousands more trough Software.",
               "About dialog, 'About' tab text"),
            // tr("LXQt would not have been possible without the <a %1>Razor-qt</a> project and its many contributors.",
            //    "About dialog, 'About' tab text").arg(QStringLiteral("href=\"https://blog.lxde.org/2014/11/21/in-memory-of-razor-qt/\"")),
            // tr("Copyright: © %1-%2 %3", "About dialog, 'About' tab text")
            //     .arg(QStringLiteral("2010"), QDate::currentDate().toString(QStringLiteral("yyyy")), QStringLiteral("LXQt team")),
            tr("Homepage: %1", "About dialog, 'About' tab text")
                .arg(QStringLiteral("<a href=\"https://www.pantherx.org\">https://www.pantherx.org</a>")),
           tr("Wiki: %1", "About dialog, 'About' tab text")
                .arg(QStringLiteral("<a href=\"https://wiki.pantherx.org\">https://wiki.pantherx.org</a>")),
           tr("Forum: %1", "About dialog, 'About' tab text")
                .arg(QStringLiteral("<a href=\"https://community.pantherx.org\">https://community.pantherx.org</a>"))
            // tr("License: %1", "About dialog, 'About' tab text")
            //     .arg(QStringLiteral("<a href=\"https://www.gnu.org/licenses/lgpl-2.1.html\">GNU Lesser General Public License version 2.1 or later</a>"
            //          " and partly under the "
            //          "<a href=\"https://www.gnu.org/licenses/gpl-2.0.html\">GNU General Public License version 2</a>"))
            );
}

QString AboutDialogPrivate::authorsText() const
{
    return QStringLiteral("<p>%1</p><p>%2</p>").arg(
                tr("PantherX is developed by the <a %1>PantherX Team and contributors</a>.", "About dialog, 'Authors' tab text")
                    .arg(QStringLiteral("href=\"https://www.pantherx.org/about\"")),
                tr("If you are interested in working with our development team, <a %1>join us</a>.", "About dialog, 'Authors' tab text")
                    .arg(QStringLiteral("href=\"https://www.pantherx.org/contact\""))
                );
}


AboutDialog::AboutDialog()
{
    d_ptr = new AboutDialogPrivate();
}

void AboutDialogPrivate::copyToCliboardTechInfo()
{
    TechnicalInfo info;
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(info.text());
}
