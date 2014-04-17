include $(top_srcdir)/src/Makefile.include

AM_CPPFLAGS += -I$(top_srcdir)/src \
  -I$(top_builddir)/src/qt \
  -I$(top_builddir)/src/qt/forms \
  $(PROTOBUF_CFLAGS) \
  $(QR_CFLAGS)
bin_PROGRAMS = digibyte-qt
noinst_LIBRARIES = libdigibyteqt.a
SUBDIRS = $(BUILD_TEST_QT)
DIST_SUBDIRS = test

# digibyte qt core #
QT_TS = \
  locale/digibyte_ach.ts \
  locale/digibyte_af_ZA.ts \
  locale/digibyte_ar.ts \
  locale/digibyte_be_BY.ts \
  locale/digibyte_bg.ts \
  locale/digibyte_bs.ts \
  locale/digibyte_ca_ES.ts \
  locale/digibyte_ca.ts \
  locale/digibyte_ca@valencia.ts \
  locale/digibyte_cmn.ts \
  locale/digibyte_cs.ts \
  locale/digibyte_cy.ts \
  locale/digibyte_da.ts \
  locale/digibyte_de_AT.ts \
  locale/digibyte_de.ts \
  locale/digibyte_el_GR.ts \
  locale/digibyte_en.ts \
  locale/digibyte_eo.ts \
  locale/digibyte_es_CL.ts \
  locale/digibyte_es_DO.ts \
  locale/digibyte_es_MX.ts \
  locale/digibyte_es.ts \
  locale/digibyte_es_UY.ts \
  locale/digibyte_et.ts \
  locale/digibyte_eu_ES.ts \
  locale/digibyte_fa_IR.ts \
  locale/digibyte_fa.ts \
  locale/digibyte_fi.ts \
  locale/digibyte_fr_CA.ts \
  locale/digibyte_fr.ts \
  locale/digibyte_gl.ts \
  locale/digibyte_gu_IN.ts \
  locale/digibyte_he.ts \
  locale/digibyte_hi_IN.ts \
  locale/digibyte_hr.ts \
  locale/digibyte_hu.ts \
  locale/digibyte_id_ID.ts \
  locale/digibyte_it.ts \
  locale/digibyte_ja.ts \
  locale/digibyte_ka.ts \
  locale/digibyte_kk_KZ.ts \
  locale/digibyte_ko_KR.ts \
  locale/digibyte_ky.ts \
  locale/digibyte_la.ts \
  locale/digibyte_lt.ts \
  locale/digibyte_lv_LV.ts \
  locale/digibyte_ms_MY.ts \
  locale/digibyte_nb.ts \
  locale/digibyte_nl.ts \
  locale/digibyte_pam.ts \
  locale/digibyte_pl.ts \
  locale/digibyte_pt_BR.ts \
  locale/digibyte_pt_PT.ts \
  locale/digibyte_ro_RO.ts \
  locale/digibyte_ru.ts \
  locale/digibyte_sah.ts \
  locale/digibyte_sk.ts \
  locale/digibyte_sl_SI.ts \
  locale/digibyte_sq.ts \
  locale/digibyte_sr.ts \
  locale/digibyte_sv.ts \
  locale/digibyte_th_TH.ts \
  locale/digibyte_tr.ts \
  locale/digibyte_uk.ts \
  locale/digibyte_ur_PK.ts \
  locale/digibyte_uz@Cyrl.ts \
  locale/digibyte_vi.ts \
  locale/digibyte_vi_VN.ts \
  locale/digibyte_zh_CN.ts \
  locale/digibyte_zh_HK.ts \
  locale/digibyte_zh_TW.ts

QT_FORMS_UI = \
  forms/aboutdialog.ui \
  forms/addressbookpage.ui \
  forms/askpassphrasedialog.ui \
  forms/coincontroldialog.ui \
  forms/editaddressdialog.ui \
  forms/helpmessagedialog.ui \
  forms/intro.ui \
  forms/openuridialog.ui \
  forms/optionsdialog.ui \
  forms/overviewpage.ui \
  forms/receivecoinsdialog.ui \
  forms/receiverequestdialog.ui \
  forms/rpcconsole.ui \
  forms/sendcoinsdialog.ui \
  forms/sendcoinsentry.ui \
  forms/signverifymessagedialog.ui \
  forms/transactiondescdialog.ui

QT_MOC_CPP = \
  moc_addressbookpage.cpp \
  moc_addresstablemodel.cpp \
  moc_askpassphrasedialog.cpp \
  moc_digibyteaddressvalidator.cpp \
  moc_digibyteamountfield.cpp \
  moc_digibytegui.cpp \
  moc_digibyteunits.cpp \
  moc_clientmodel.cpp \
  moc_coincontroldialog.cpp \
  moc_coincontroltreewidget.cpp \
  moc_csvmodelwriter.cpp \
  moc_editaddressdialog.cpp \
  moc_guiutil.cpp \
  moc_intro.cpp \
  moc_macdockiconhandler.cpp \
  moc_macnotificationhandler.cpp \
  moc_monitoreddatamapper.cpp \
  moc_notificator.cpp \
  moc_openuridialog.cpp \
  moc_optionsdialog.cpp \
  moc_optionsmodel.cpp \
  moc_overviewpage.cpp \
  moc_paymentserver.cpp \
  moc_qvalidatedlineedit.cpp \
  moc_qvaluecombobox.cpp \
  moc_receivecoinsdialog.cpp \
  moc_receiverequestdialog.cpp \
  moc_recentrequeststablemodel.cpp \
  moc_rpcconsole.cpp \
  moc_sendcoinsdialog.cpp \
  moc_sendcoinsentry.cpp \
  moc_signverifymessagedialog.cpp \
  moc_splashscreen.cpp \
  moc_trafficgraphwidget.cpp \
  moc_transactiondesc.cpp \
  moc_transactiondescdialog.cpp \
  moc_transactionfilterproxy.cpp \
  moc_transactiontablemodel.cpp \
  moc_transactionview.cpp \
  moc_utilitydialog.cpp \
  moc_walletframe.cpp \
  moc_walletmodel.cpp \
  moc_walletview.cpp

DIGIBYTE_MM = \
  macdockiconhandler.mm \
  macnotificationhandler.mm

QT_MOC = \
  digibyte.moc \
  intro.moc \
  overviewpage.moc \
  rpcconsole.moc

QT_QRC_CPP = qrc_digibyte.cpp
QT_QRC = digibyte.qrc

PROTOBUF_CC = paymentrequest.pb.cc
PROTOBUF_H = paymentrequest.pb.h
PROTOBUF_PROTO = paymentrequest.proto

DIGIBYTE_QT_H = \
  addressbookpage.h \
  addresstablemodel.h \
  askpassphrasedialog.h \
  digibyteaddressvalidator.h \
  digibyteamountfield.h \
  digibytegui.h \
  digibyteunits.h \
  clientmodel.h \
  coincontroldialog.h \
  coincontroltreewidget.h \
  csvmodelwriter.h \
  editaddressdialog.h \
  guiconstants.h \
  guiutil.h \
  intro.h \
  macdockiconhandler.h \
  macnotificationhandler.h \
  monitoreddatamapper.h \
  notificator.h \
  openuridialog.h \
  optionsdialog.h \
  optionsmodel.h \
  overviewpage.h \
  paymentrequestplus.h \
  paymentserver.h \
  qvalidatedlineedit.h \
  qvaluecombobox.h \
  receivecoinsdialog.h \
  receiverequestdialog.h \
  recentrequeststablemodel.h \
  rpcconsole.h \
  sendcoinsdialog.h \
  sendcoinsentry.h \
  signverifymessagedialog.h \
  splashscreen.h \
  trafficgraphwidget.h \
  transactiondesc.h \
  transactiondescdialog.h \
  transactionfilterproxy.h \
  transactionrecord.h \
  transactiontablemodel.h \
  transactionview.h \
  utilitydialog.h \
  walletframe.h \
  walletmodel.h \
  walletmodeltransaction.h \
  walletview.h

RES_ICONS = \
  res/icons/add.png \
  res/icons/address-book.png \
  res/icons/digibyte.ico \
  res/icons/digibyte.png \
  res/icons/digibyte_testnet.ico \
  res/icons/digibyte_testnet.png \
  res/icons/clock1.png \
  res/icons/clock2.png \
  res/icons/clock3.png \
  res/icons/clock4.png \
  res/icons/clock5.png \
  res/icons/configure.png \
  res/icons/connect0_16.png \
  res/icons/connect1_16.png \
  res/icons/connect2_16.png \
  res/icons/connect3_16.png \
  res/icons/connect4_16.png \
  res/icons/debugwindow.png \
  res/icons/edit.png \
  res/icons/editcopy.png \
  res/icons/editpaste.png \
  res/icons/export.png \
  res/icons/filesave.png \
  res/icons/history.png \
  res/icons/key.png \
  res/icons/lock_closed.png \
  res/icons/lock_open.png \
  res/icons/overview.png \
  res/icons/qrcode.png \
  res/icons/quit.png \
  res/icons/receive.png \
  res/icons/remove.png \
  res/icons/send.png \
  res/icons/synced.png \
  res/icons/toolbar.png \
  res/icons/toolbar_testnet.png \
  res/icons/transaction0.png \
  res/icons/transaction2.png \
  res/icons/transaction_conflicted.png \
  res/icons/tx_inout.png \
  res/icons/tx_input.png \
  res/icons/tx_output.png \
  res/icons/tx_mined.png

DIGIBYTE_QT_CPP = \
  digibyte.cpp \
  digibyteaddressvalidator.cpp \
  digibyteamountfield.cpp \
  digibytegui.cpp \
  digibyteunits.cpp \
  clientmodel.cpp \
  csvmodelwriter.cpp \
  guiutil.cpp \
  intro.cpp \
  monitoreddatamapper.cpp \
  notificator.cpp \
  optionsdialog.cpp \
  optionsmodel.cpp \
  qvalidatedlineedit.cpp \
  qvaluecombobox.cpp \
  rpcconsole.cpp \
  signverifymessagedialog.cpp \
  splashscreen.cpp \
  trafficgraphwidget.cpp \
  utilitydialog.cpp

if ENABLE_WALLET
DIGIBYTE_QT_CPP += \
  addressbookpage.cpp \
  addresstablemodel.cpp \
  askpassphrasedialog.cpp \
  coincontroldialog.cpp \
  coincontroltreewidget.cpp \
  editaddressdialog.cpp \
  openuridialog.cpp \
  overviewpage.cpp \
  paymentrequestplus.cpp \
  paymentserver.cpp \
  receivecoinsdialog.cpp \
  receiverequestdialog.cpp \
  recentrequeststablemodel.cpp \
  sendcoinsdialog.cpp \
  sendcoinsentry.cpp \
  transactiondesc.cpp \
  transactiondescdialog.cpp \
  transactionfilterproxy.cpp \
  transactionrecord.cpp \
  transactiontablemodel.cpp \
  transactionview.cpp \
  walletframe.cpp \
  walletmodel.cpp \
  walletmodeltransaction.cpp \
  walletview.cpp
endif

RES_IMAGES = \
  res/images/about.png \
  res/images/splash.png \
  res/images/splash_testnet.png

RES_MOVIES = $(wildcard res/movies/spinner-*.png)

DIGIBYTE_RC = res/digibyte-qt-res.rc

libdigibyteqt_a_CPPFLAGS = $(AM_CPPFLAGS) $(QT_INCLUDES) \
  -I$(top_srcdir)/src/qt/forms $(QT_DBUS_INCLUDES)
libdigibyteqt_a_SOURCES = $(DIGIBYTE_QT_CPP) $(DIGIBYTE_QT_H) $(QT_FORMS_UI) \
  $(QT_QRC) $(QT_TS) $(PROTOBUF_PROTO) $(RES_ICONS) $(RES_IMAGES) $(RES_MOVIES)

nodist_libdigibyteqt_a_SOURCES = $(QT_MOC_CPP) $(QT_MOC) $(PROTOBUF_CC) \
  $(PROTOBUF_H) $(QT_QRC_CPP)

BUILT_SOURCES = $(nodist_libdigibyteqt_a_SOURCES)

#Generating these with a half-written protobuf header leads to wacky results.
#This makes sure it's done.
$(QT_MOC): $(PROTOBUF_H)
$(QT_MOC_CPP): $(PROTOBUF_H)

# digibyte-qt binary #
digibyte_qt_CPPFLAGS = $(AM_CPPFLAGS) $(QT_INCLUDES) \
  -I$(top_srcdir)/src/qt/forms
digibyte_qt_SOURCES = digibyte.cpp
if TARGET_DARWIN
  digibyte_qt_SOURCES += $(DIGIBYTE_MM)
endif
if TARGET_WINDOWS
  digibyte_qt_SOURCES += $(DIGIBYTE_RC)
endif
digibyte_qt_LDADD = libdigibyteqt.a $(LIBDIGIBYTE_SERVER)
if ENABLE_WALLET
digibyte_qt_LDADD += $(LIBDIGIBYTE_WALLET)
endif
digibyte_qt_LDADD += $(LIBDIGIBYTE_CLI) $(LIBDIGIBYTE_COMMON) $(LIBLEVELDB) $(LIBMEMENV) \
  $(BOOST_LIBS) $(QT_LIBS) $(QT_DBUS_LIBS) $(QR_LIBS) $(PROTOBUF_LIBS) $(BDB_LIBS)
digibyte_qt_LDFLAGS = $(QT_LDFLAGS)

# forms/foo.h -> forms/ui_foo.h
QT_FORMS_H=$(join $(dir $(QT_FORMS_UI)),$(addprefix ui_, $(notdir $(QT_FORMS_UI:.ui=.h))))

#locale/foo.ts -> locale/foo.qm
QT_QM=$(QT_TS:.ts=.qm)

.PHONY: FORCE
.SECONDARY: $(QT_QM)

digibytestrings.cpp: FORCE
	$(MAKE) -C $(top_srcdir)/src qt/digibytestrings.cpp

translate: digibytestrings.cpp $(QT_FORMS_UI) $(QT_FORMS_UI) $(DIGIBYTE_QT_CPP) $(DIGIBYTE_QT_H) $(DIGIBYTE_MM)
	@test -n $(LUPDATE) || echo "lupdate is required for updating translations"
	@QT_SELECT=$(QT_SELECT) $(LUPDATE) $^ -locations relative -no-obsolete -ts locale/digibyte_en.ts

$(QT_QRC_CPP): $(QT_QRC) $(QT_QM) $(QT_FORMS_H) $(RES_ICONS) $(RES_IMAGES) $(RES_MOVIES) $(PROTOBUF_H)
	@cd $(abs_srcdir); test -f $(RCC) && QT_SELECT=$(QT_SELECT) $(RCC) -name digibyte -o $(abs_builddir)/$@ $< || \
	  echo error: could not build $@
	$(SED) -i.bak -e '/^\*\*.*Created:/d' $@ && rm $@.bak
	$(SED) -i.bak -e '/^\*\*.*by:/d' $@ && rm $@.bak

CLEANFILES = $(BUILT_SOURCES) $(QT_QM) $(QT_FORMS_H) *.gcda *.gcno
