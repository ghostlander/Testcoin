#ifndef ADDRESSBOOKPAGE_H
#define ADDRESSBOOKPAGE_H

#include <QDialog>

namespace Ui {
    class AddressBookPage;
}
class AddressTableModel;
class OptionsModel;

QT_BEGIN_NAMESPACE
class QTableView;
class QItemSelection;
class QSortFilterProxyModel;
class QMenu;
class QModelIndex;
QT_END_NAMESPACE

/** Widget that shows a list of sending or receiving addresses.
  */
class AddressBookPage : public QDialog
{
    Q_OBJECT

public:
    enum Tabs {
        SendingTab = 0,
        ReceivingTab = 1
    };

    enum Mode {
        ForSending, /**< Open address book to pick address for sending */
        ForEditing  /**< Open address book for editing */
    };

    explicit AddressBookPage(Mode mode, Tabs tab, QWidget *parent = 0);
    ~AddressBookPage();

    void setModel(AddressTableModel *model);
    void setOptionsModel(OptionsModel *optionsModel);
    const QString &getReturnValue() const { return returnValue; }

public slots:
    void done(int retval);
    void exportClicked();

private:
    Ui::AddressBookPage *ui;
    AddressTableModel *model;
    OptionsModel *optionsModel;
    Mode mode;
    Tabs tab;
    QString returnValue;
    QSortFilterProxyModel *proxyModel;
    QMenu *contextMenu;
    QAction *deleteAction;
    QString newAddressToSelect;

private slots:
    /* Delete the currently selected address entry */
    void on_deleteAddress_clicked();
    /* Create a new address for receiving coins and/or add a new address book entry */
    void on_newAddress_clicked();
    /* Copy the address of currently selected address entry to the clipboard */
    void on_copyAddress_clicked();
    /* Open the sign message tab in the Sign/Verify Message dialogue with the currently selected address */
    void on_signMessage_clicked();
    /* Open the verify message tab in the Sign/Verify Message dialogue with the currently selected address */
    void on_verifyMessage_clicked();
    /* Open a send coins dialog for the currently selected address (no button) */
    void onSendCoinsAction();
    /* Generate a QR Code from the currently selected address */
    void on_showQRCode_clicked();
    /* Copy the label of currently selected address entry to the clipboard (no button) */
    void onCopyLabelAction();
    /* Rename the label of currently selected address entry (no button) */
    void onRenameLabelAction();

    /* Set button states based on the selected tab and selection */
    void selectionChanged();
    /* Spawn the contextual menu (right mouse menu) for the address book entry */
    void contextualMenu(const QPoint &point);
    /* New entry/entries were added to the address table */
    void selectNewAddress(const QModelIndex &parent, int begin, int end);

signals:
    void signMessage(QString addr);
    void verifyMessage(QString addr);
    void sendCoins(QString addr);
};

#endif /* ADDRESSBOOKPAGE_H */
