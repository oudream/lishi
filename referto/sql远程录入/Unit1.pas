unit Unit1;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes,
  System.Variants,
  FMX.Types, FMX.Graphics, FMX.Controls, FMX.Forms, FMX.Dialogs, FMX.StdCtrls,
  System.Rtti, System.Bindings.Outputs, FMX.Bind.Editors, Data.Bind.EngExt,
  FMX.Bind.DBEngExt, Data.Bind.Components, Data.Bind.DBScope, FMX.Edit,
  FireDAC.UI.Intf, FireDAC.FMXUI.Wait, FireDAC.Stan.Intf, FireDAC.Comp.UI,
  FMX.Layouts, FMX.TabControl, FMX.ListView.Types, FMX.ListView, Data.DB,
  FMX.Objects, FireDAC.Comp.Client, Data.Win.ADODB;

type
  TForm1 = class(TForm)
    BindSourceDB1: TBindSourceDB;
    BindingsList1: TBindingsList;
    Layout1: TLayout;
    Label6: TLabel;
    TabControl1: TTabControl;
    TabItem1: TTabItem;
    TabItem2: TTabItem;
    TabItem3: TTabItem;
    Layout2: TLayout;
    Label3: TLabel;
    Emodelpy: TEdit;
    Label2: TLabel;
    Emodel: TEdit;
    labman: TLabel;
    Label4: TLabel;
    Ebegind: TEdit;
    Label5: TLabel;
    Eendd: TEdit;
    Layout3: TLayout;
    Label7: TLabel;
    Label8: TLabel;
    Ertreadwidth: TEdit;
    Label9: TLabel;
    Eftreadwidth: TEdit;
    Etrackdia: TEdit;
    Label10: TLabel;
    Ewheelbase: TEdit;
    Layout4: TLayout;
    Label11: TLabel;
    Label12: TLabel;
    Eftoetmin: TEdit;
    Label13: TLabel;
    Eftoemax: TEdit;
    Eftoe: TEdit;
    Label14: TLabel;
    Eftoemin: TEdit;
    Eftoetmax: TEdit;
    Layout5: TLayout;
    Layout6: TLayout;
    Label20: TLabel;
    Edit20: TEdit;
    Layout7: TLayout;
    Edit21: TEdit;
    Label21: TLabel;
    ListView1: TListView;
    ListView2: TListView;
    BindSourceDB2: TBindSourceDB;
    LinkFillControlToField1: TLinkFillControlToField;
    Layout8: TLayout;
    Label22: TLabel;
    Label23: TLabel;
    Efcambertmin: TEdit;
    Label24: TLabel;
    Efcambermax: TEdit;
    Efcamber: TEdit;
    Label25: TLabel;
    Efcambermin: TEdit;
    Label26: TLabel;
    Efcambert: TEdit;
    Label27: TLabel;
    Efcambertmax: TEdit;
    Layout9: TLayout;
    Label29: TLabel;
    Efbackmin: TEdit;
    Efback: TEdit;
    Label28: TLabel;
    Efbackmax: TEdit;
    Label30: TLabel;
    Layout10: TLayout;
    Eftoesum: TEdit;
    Label19: TLabel;
    Eftoesummax: TEdit;
    Label17: TLabel;
    Eftoesummin: TEdit;
    Label18: TLabel;
    Layout11: TLayout;
    Label31: TLabel;
    Label32: TLabel;
    Ertoetmax: TEdit;
    Label33: TLabel;
    Ertoemax: TEdit;
    Ertoe: TEdit;
    Label34: TLabel;
    Ertoemin: TEdit;
    Layout12: TLayout;
    Ertoesum: TEdit;
    Label37: TLabel;
    Ertoesumtmax: TEdit;
    Label38: TLabel;
    Ertoesumtmin: TEdit;
    Label39: TLabel;
    Layout13: TLayout;
    Label40: TLabel;
    Label41: TLabel;
    Ercambertmin: TEdit;
    Label42: TLabel;
    Ercambermax: TEdit;
    Ercamber: TEdit;
    Label43: TLabel;
    Ercambermin: TEdit;
    Label44: TLabel;
    Ercambert: TEdit;
    Label45: TLabel;
    Ercambertmax: TEdit;
    Layout14: TLayout;
    Label46: TLabel;
    Erbackmin: TEdit;
    Erback: TEdit;
    Label47: TLabel;
    Erbackmax: TEdit;
    Label48: TLabel;
    Ertoetmin: TEdit;
    Label49: TLabel;
    Label50: TLabel;
    Ertoet: TEdit;
    Ertoesummax: TEdit;
    Label36: TLabel;
    Ertoesummin: TEdit;
    Label35: TLabel;
    Layout15: TLayout;
    Erthrust: TEdit;
    Erthrustmax: TEdit;
    Label51: TLabel;
    Label52: TLabel;
    Erthrustmin: TEdit;
    Label53: TLabel;
    Layout16: TLayout;
    Label54: TLabel;
    Label55: TLabel;
    Ekpicastertmin: TEdit;
    Label56: TLabel;
    Ekpicastermax: TEdit;
    Ekpicaster: TEdit;
    Label57: TLabel;
    Ekpicastermin: TEdit;
    Label58: TLabel;
    Ekpicastert: TEdit;
    Label59: TLabel;
    Ekpicastertmax: TEdit;
    Layout17: TLayout;
    Label60: TLabel;
    Label61: TLabel;
    Ekpicambertmin: TEdit;
    Label62: TLabel;
    Ekpicambermax: TEdit;
    Ekpicamber: TEdit;
    Label63: TLabel;
    Ekpicambermin: TEdit;
    Label64: TLabel;
    Ekpicambert: TEdit;
    Label65: TLabel;
    Ekpicambertmax: TEdit;
    Label66: TLabel;
    Label15: TLabel;
    Eftoesumtmin: TEdit;
    Label16: TLabel;
    Eftoesumtmax: TEdit;
    Layout18: TLayout;
    Button1: TButton;
    LinkControlToField3: TLinkControlToField;
    LinkControlToField4: TLinkControlToField;
    LinkControlToField5: TLinkControlToField;
    LinkControlToField6: TLinkControlToField;
    LinkControlToField7: TLinkControlToField;
    LinkControlToField8: TLinkControlToField;
    LinkControlToField9: TLinkControlToField;
    LinkControlToField10: TLinkControlToField;
    LinkControlToField11: TLinkControlToField;
    LinkControlToField12: TLinkControlToField;
    LinkControlToField13: TLinkControlToField;
    LinkControlToField14: TLinkControlToField;
    LinkControlToField15: TLinkControlToField;
    LinkControlToField16: TLinkControlToField;
    LinkControlToField17: TLinkControlToField;
    LinkControlToField18: TLinkControlToField;
    LinkControlToField19: TLinkControlToField;
    LinkControlToField20: TLinkControlToField;
    LinkControlToField21: TLinkControlToField;
    LinkControlToField22: TLinkControlToField;
    LinkControlToField23: TLinkControlToField;
    LinkControlToField24: TLinkControlToField;
    LinkControlToField25: TLinkControlToField;
    LinkControlToField26: TLinkControlToField;
    LinkControlToField27: TLinkControlToField;
    LinkControlToField28: TLinkControlToField;
    LinkControlToField29: TLinkControlToField;
    LinkControlToField30: TLinkControlToField;
    LinkControlToField31: TLinkControlToField;
    LinkControlToField32: TLinkControlToField;
    LinkControlToField33: TLinkControlToField;
    LinkControlToField34: TLinkControlToField;
    LinkControlToField35: TLinkControlToField;
    LinkControlToField36: TLinkControlToField;
    LinkControlToField37: TLinkControlToField;
    LinkControlToField38: TLinkControlToField;
    LinkControlToField39: TLinkControlToField;
    LinkControlToField40: TLinkControlToField;
    LinkControlToField41: TLinkControlToField;
    LinkControlToField42: TLinkControlToField;
    LinkControlToField43: TLinkControlToField;
    LinkControlToField44: TLinkControlToField;
    LinkControlToField45: TLinkControlToField;
    LinkControlToField46: TLinkControlToField;
    LinkControlToField47: TLinkControlToField;
    LinkControlToField48: TLinkControlToField;
    LinkControlToField49: TLinkControlToField;
    LinkControlToField50: TLinkControlToField;
    LinkControlToField51: TLinkControlToField;
    LinkControlToField52: TLinkControlToField;
    LinkControlToField53: TLinkControlToField;
    LinkControlToField54: TLinkControlToField;
    LinkControlToField55: TLinkControlToField;
    LinkControlToField56: TLinkControlToField;
    LinkControlToField57: TLinkControlToField;
    LinkControlToField58: TLinkControlToField;
    LinkControlToField59: TLinkControlToField;
    LinkControlToField60: TLinkControlToField;
    LinkControlToField61: TLinkControlToField;
    LinkControlToField62: TLinkControlToField;
    Button3: TButton;
    Layout19: TLayout;
    Button8: TButton;
    Layout20: TLayout;
    Button10: TButton;
    Button11: TButton;
    Button12: TButton;
    Button2: TButton;
    Image3: TImage;
    Image1: TImage;
    BindSourceDB3: TBindSourceDB;
    LinkFillControlToField2: TLinkFillControlToField;
    Tbiman: TTabItem;
    Label68: TLabel;
    edmanpy: TEdit;
    Label69: TLabel;
    Label70: TLabel;
    Edmanname: TEdit;
    Imglogo: TImage;
    Button5: TButton;
    OpenDialog1: TOpenDialog;
    Button4: TButton;
    Button6: TButton;
    Label67: TLabel;
    lman: TLabel;
    BindSourceDB4: TBindSourceDB;
    LinkControlToField1: TLinkControlToField;
    Image2: TImage;
    procedure FormShow(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button11Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button10Click(Sender: TObject);
    procedure Button12Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Edit20ChangeTracking(Sender: TObject);
    procedure Edit21ChangeTracking(Sender: TObject);
    procedure ListView1ItemClick(const Sender: TObject;
      const AItem: TListViewItem);
    procedure ListView2ItemClick(const Sender: TObject;
      const AItem: TListViewItem);
    procedure Button5Click(Sender: TObject);
    procedure ImglogoClick(Sender: TObject);
  private
    { Private declarations }
  public
    procedure fillveh;
    procedure fillvehfw; // 前轮数据
    procedure fillvehrw; // 前轮数据
    procedure saveveh;
    procedure savevehf; // 前轮数据
    procedure savevehr;
    procedure updateveh;
    procedure updatevehf;
    procedure updatevehr;
    procedure findlike(fdq: TadoQuery; dataname, itemname, strlike: string);
    procedure saveman(manname, manpy: string; manlogo: tbitmap);
    { Public declarations }
  end;

type
  TVehData = record
    manname: String; // 制造商
    manpy: String; // 制造商简拼
    ModelName: String; // 车型
    ModelPy: String; // 车型简拼
    BeginDT: String; // Integer;//年份
    EndDT: String; // Integer;//年份
    Vehphoto: TBlobField; // add by qiujing 2013.11.7
    // Rsuspension:string;//后悬挂
    // Fsuspension:string;//前悬挂
    WheelBase: Real; // 轴距.车型
    TrackDia: Real; // 轮径(车型.四轮一致)

    FTreadWidth: Real; // 前轮.轮距.车型
    RTreadWidth: Real; // 后轮.轮距.车型

    FToeMin: Real; // 前轮.前束(度).最小
    FToeMax: Real; // 前轮.前束(度).最大
    FToeT: Real; // 前轮.前束(度).左右差
    FToeTmin: Real; // 前轮.前束(度).左右差
    FToeTmax: Real; // 前轮.前束(度).左右差
    FToe: Real; // 前轮.前束(度).车型

    FToeSumMin: Real; // 前轮.总前束(度).最小
    FToeSumMax: Real; // 前轮.总前束(度).最大
    FToeSum: Real; // 前轮.总前束(度).车型

    FToesumTmin: Real; // 前轮.总前束(度).左右差
    FToesumTmax: Real; // 前轮.总前束(度).左右差

    FCamberMin: Real; // 前轮.外倾(度).最小
    FCamberMax: Real; // 前轮.外倾(度).最大
    FCamberT: Real; // 前轮.外倾(度).左右差
    FCamberTmin: Real; // 前轮.外倾(度).左右差
    FCamberTmax: Real; // 前轮.外倾(度).左右差

    FCamber: Real; // 前轮.外倾(度).车型

    FBackMin: Real; // 前轮.退缩角(度).最小
    FBackMax: Real; // 前轮.退缩角(度).最大
    FBack: Real; // 前轮.退缩角(度).车型

    RToeMin: Real; // 后轮.前束(度).最小
    RToeMax: Real; // 后轮.前束(度).最大
    RToeT: Real; // 后轮.前束(度).左右差
    RToetMin: Real; // 后轮.前束(度).最小
    RToetMax: Real; // 后轮.前束(度).最大
    RToe: Real; // 后轮.前束(度).车型

    RToeSumMin: Real; // 后轮.总前束(度).最小
    RToeSumMax: Real; // 后轮.总前束(度).最大
    RToeSum: Real; // 后轮.总前束(度).车型
    RToeSumtMin: Real;
    RToeSumtMax: Real;

    RCamberMin: Real; // 后轮.外倾(度).最小
    RCamberMax: Real; // 后轮.外倾(度).最大
    RCamberT: Real; // 后轮.外倾(度).左右差
    RCambertMin: Real;
    RCambertMax: Real;
    RCamber: Real; // 后轮.外倾(度).车型

    RBackMin: Real; // 后轮.退缩角(度).最小
    RBackMax: Real; // 后轮.退缩角(度).最大
    RBack: Real; // 后轮.退缩角(度).车型

    RThrustMin: Real; // 后轮.推进角(度).最小
    RThrustMax: Real; // 后轮.推进角(度).最大

    RThrust: Real; // 后轮.推进角(度).车型

    KpiCamberMin: Real; // 主销.内倾(度).最小
    KpiCamberMax: Real; // 主销.内倾(度).最大
    KpiCamberT: Real; // 主销.内倾(度).左右差
    KpiCambertMin: Real;
    KpiCambertMax: Real;
    KpiCamber: Real; // 主销.内倾(度).车型

    KpiCasterMin: Real; // 主销.后倾(度).最小
    KpiCasterMax: Real; // 主销.后倾(度).最大
    KpiCasterT: Real; // 主销.后倾(度).左右差
    KpiCastertMin: Real;
    KpiCastertMax: Real;
    KpiCaster: Real; // 主销.后倾(度).车型
  end;

var
  Form1: TForm1;
  vehpara: TVehData;
  sqlmanname, sqlmodelname: string;
  loginok: boolean;
  loginname: string;

implementation

uses unit2, unitlogin;
{$R *.fmx}

procedure TForm1.Button10Click(Sender: TObject);
begin
  // 修改某车型参数
  // if vehpara.ModelName=trim(Emodel.Text) then
  // begin
  fillveh;
  fillvehfw; // 前轮数据
  fillvehrw; // 后轮数据
  updateveh;
  updatevehf;
  updatevehr;
  // end;
end;

procedure TForm1.Button11Click(Sender: TObject);
begin
  // close;
  application.Terminate;
end;

procedure TForm1.Button12Click(Sender: TObject);
var
  ModelName: string;
begin
  // 先查是否重复，如果型号重复不运行插入！！！
  if vehpara.manname = '' then
  begin
    messagedlg('请选择车品牌', TMsgDlgType.mtWarning, [TMsgDlgBtn.mbYes], 0);
    exit;
  end;
  ModelName := trim(Emodel.text);
  vehpara.ModelName := ModelName;
  DataModule2.FDQfindveh.Active := false;
  DataModule2.FDQfindveh.SQL.Clear;
  DataModule2.FDQfindveh.SQL.Add('select modelname from vehicle where manname='
    + quotedstr(vehpara.manname) + ' and modelname=' + quotedstr(ModelName));
  DataModule2.FDQfindveh.Active := true;
  if DataModule2.FDQfindveh.RecordCount = 0 then
    if (ModelName <> '') then
    begin
      fillveh;
      saveveh;
      fillvehfw; // 前轮数据
      savevehf; // 前轮数据
      fillvehrw; // 后轮数据
      savevehr;
    end;

end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  DataModule2.FDQveh.Active := false;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  TabControl1.ActiveTab := TabItem1;
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  TabControl1.ActiveTab := TabItem2;
end;

procedure TForm1.Button5Click(Sender: TObject);
var
  strname: string;
begin
  // 不允许重复添加品牌
  strname := trim(Edmanname.text);
  DataModule2.FDQsaveman.Active := false;
  DataModule2.FDQsaveman.SQL.Clear;
  DataModule2.FDQsaveman.SQL.Add('select manname from man where manname=' +
    quotedstr(strname));
  DataModule2.FDQsaveman.Active := true;
  if DataModule2.FDQsaveman.RecordCount = 0 then
    if (strname <> '') then
    begin
      saveman(Edmanname.text, edmanpy.text, Imglogo.Bitmap);
      // oldmanid:=oldmanid+1;
      // DataModule2.FDQsaveman.Active:=false;
      // DataModule2.FDQsaveman.Active:=true;
    end;

end;

procedure TForm1.Button8Click(Sender: TObject);
begin
  TabControl1.ActiveTab := TabItem3;
end;

procedure TForm1.Edit20ChangeTracking(Sender: TObject);
begin
  findlike(DataModule2.FDQman, 'man', 'manname', Edit20.text);
end;

procedure TForm1.Edit21ChangeTracking(Sender: TObject);
var
  str: string;
begin
  DataModule2.FDQveh.SQL.Clear;
  str := 'select * from vehicle where modelname like ' +
    quotedstr('%' + Edit21.text + '%') + ' and manname=' +
    quotedstr(sqlmanname);
  DataModule2.FDQveh.SQL.Add(str);
  DataModule2.FDQveh.Active := true;
  // findlike(DataModule2.FDQveh,'vehicle','manname',Edit21.text);
end;

procedure TForm1.fillveh;
begin

  vehpara.ModelPy := Emodelpy.text;
  vehpara.BeginDT := Ebegind.text;
  vehpara.EndDT := Eendd.text;
  vehpara.WheelBase := StrToFloatDef(Ewheelbase.text, 0);
  vehpara.TrackDia := StrToFloatDef(Etrackdia.text, 0);
  vehpara.FTreadWidth := StrToFloatDef(Eftreadwidth.text, 0);
  vehpara.RTreadWidth := StrToFloatDef(Ertreadwidth.text, 0);
  vehpara.KpiCasterMin := StrToFloatDef(Ekpicastermin.text, 0);
  vehpara.KpiCaster := StrToFloatDef(Ekpicaster.text, 0);
  vehpara.KpiCasterMax := StrToFloatDef(Ekpicastermax.text, 0);
  vehpara.KpiCastertMin := StrToFloatDef(Ekpicastertmin.text, 0);
  vehpara.KpiCasterT := StrToFloatDef(Ekpicastert.text, 0);
  vehpara.KpiCastertMax := StrToFloatDef(Ekpicastertmax.text, 0);
  vehpara.KpiCamberMin := StrToFloatDef(Ekpicambermin.text, 0);
  vehpara.KpiCamber := StrToFloatDef(Ekpicamber.text, 0);
  vehpara.KpiCamberMax := StrToFloatDef(Ekpicambermax.text, 0);
  vehpara.KpiCambertMin := StrToFloatDef(Ekpicambertmin.text, 0);
  vehpara.KpiCamberT := StrToFloatDef(Ekpicambert.text, 0);
  vehpara.KpiCambertMax := StrToFloatDef(Ekpicambertmax.text, 0);
end;

procedure TForm1.fillvehfw;
begin
  // 填充前轮 数据
  vehpara.FToeMin := StrToFloatDef(Eftoemin.text, 0);
  vehpara.FToe := StrToFloatDef(Eftoe.text, 0);
  vehpara.FToeMax := StrToFloatDef(Eftoemax.text, 0);
  vehpara.FToeTmin := StrToFloatDef(Eftoetmin.text, 0);
  vehpara.FToeTmax := StrToFloatDef(Eftoetmax.text, 0);
  vehpara.FToeSumMin := StrToFloatDef(Eftoesummin.text, 0);
  vehpara.FToeSum := StrToFloatDef(Eftoesum.text, 0);
  vehpara.FToeSumMax := StrToFloatDef(Eftoesummax.text, 0);
  vehpara.FToesumTmin := StrToFloatDef(Eftoesumtmin.text, 0);
  vehpara.FToesumTmax := StrToFloatDef(Eftoesumtmax.text, 0);
  vehpara.FCamberMin := StrToFloatDef(Efcambermin.text, 0);
  vehpara.FCamber := StrToFloatDef(Efcamber.text, 0);
  vehpara.FCamberMax := StrToFloatDef(Efcambermax.text, 0);
  vehpara.FCamberTmin := StrToFloatDef(Efcambertmin.text, 0);
  vehpara.FCamberT := StrToFloatDef(Efcambert.text, 0);
  vehpara.FCamberTmax := StrToFloatDef(Efcambertmax.text, 0);
  vehpara.FBackMin := StrToFloatDef(Efbackmin.text, 0);
  vehpara.FBack := StrToFloatDef(Efback.text, 0);
  vehpara.FBackMax := StrToFloatDef(Efbackmax.text, 0);
end;

procedure TForm1.fillvehrw;
begin
  // 填充后轮 数据
  vehpara.RToeMin := StrToFloatDef(Ertoemin.text, 0);
  vehpara.RToe := StrToFloatDef(Ertoe.text, 0);
  vehpara.RToeMax := StrToFloatDef(Ertoemax.text, 0);
  vehpara.RToetMin := StrToFloatDef(Ertoetmin.text, 0);
  vehpara.RToeT := StrToFloatDef(Ertoet.text, 0);
  vehpara.RToetMax := StrToFloatDef(Ertoetmax.text, 0);
  vehpara.RToeSumMin := StrToFloatDef(Ertoesummin.text, 0);
  vehpara.RToeSum := StrToFloatDef(Ertoesum.text, 0);
  vehpara.RToeSumMax := StrToFloatDef(Ertoesummax.text, 0);
  vehpara.RToeSumtMin := StrToFloatDef(Ertoesumtmin.text, 0);
  vehpara.RToeSumtMax := StrToFloatDef(Ertoesumtmax.text, 0);
  vehpara.RCamberMin := StrToFloatDef(Ercambermin.text, 0);
  vehpara.RCamber := StrToFloatDef(Ercamber.text, 0);
  vehpara.RCamberMax := StrToFloatDef(Ercambermax.text, 0);
  vehpara.RCambertMin := StrToFloatDef(Ercambertmin.text, 0);
  vehpara.RCambertMax := StrToFloatDef(Ercambertmax.text, 0);
  vehpara.RCamberT := StrToFloatDef(Ercambert.text, 0);
  vehpara.RBackMin := StrToFloatDef(Erbackmin.text, 0);
  vehpara.RBack := StrToFloatDef(Erback.text, 0);
  vehpara.RBackMax := StrToFloatDef(Erbackmax.text, 0);
  vehpara.RThrustMin := StrToFloatDef(Erthrustmin.text, 0);
  vehpara.RThrust := StrToFloatDef(Erthrust.text, 0);
  vehpara.RThrustMax := StrToFloatDef(Erthrustmax.text, 0);
end;

procedure TForm1.findlike(fdq: TadoQuery; dataname, itemname, strlike: string);
var
  str: string;
begin
  fdq.SQL.Clear;
  str := 'select top 8 manname,manlogo from ' + dataname + ' where ' + itemname
    + ' like ' + quotedstr('%' + strlike + '%');
  fdq.SQL.Add(str);
  fdq.Active := true;
end;

procedure TForm1.FormShow(Sender: TObject);

begin
  if not loginok then
    application.Terminate;
  DataModule2.FDQveh.Active := true;

end;

procedure TForm1.ImglogoClick(Sender: TObject);
begin
  if OpenDialog1.Execute then
  begin
    Imglogo.Bitmap.LoadFromFile(OpenDialog1.FileName);
  end;
end;

procedure TForm1.ListView1ItemClick(const Sender: TObject;
  const AItem: TListViewItem);
begin
  sqlmanname := AItem.text;
  // sqlbitmap:=aite.Bitmap;
  DataModule2.FDQfindveh.SQL.Clear;
  DataModule2.FDQfindveh.SQL.Add('select * from vehicle where manname=' +
    quotedstr(AItem.text));
  DataModule2.FDQfindveh.Active := true;
  // 下面为还没有型号的情况
  DataModule2.FDQsaveman.SQL.Clear;
  DataModule2.FDQsaveman.SQL.Add('select manname,manpy from man where manname='
    + quotedstr(AItem.text));
  DataModule2.FDQsaveman.Active := true;

  vehpara.manname := DataModule2.FDQsaveman.FieldByName('manname').AsString;
  vehpara.manpy := DataModule2.FDQsaveman.FieldByName('manpy').AsString;
  lman.text := vehpara.manname;

end;

procedure TForm1.ListView2ItemClick(const Sender: TObject;
  const AItem: TListViewItem);
begin
  sqlmodelname := AItem.text;
  vehpara.ModelName := sqlmodelname;
  DataModule2.FDQveh.SQL.Clear;
  DataModule2.FDQveh.SQL.Add('select * from vehicle where modelname=' +
    quotedstr(sqlmodelname));
  DataModule2.FDQveh.Active := true;
  if sqlmanname = '' then
  begin
    sqlmanname := DataModule2.FDQveh.FieldByName('manname').AsString;
  end;
  TabControl1.ActiveTab := TabItem1;
end;

procedure TForm1.saveman(manname, manpy: string; manlogo: tbitmap);
begin
  DataModule2.FDQsaveman.SQL.Clear;
  DataModule2.FDQsaveman.SQL.Add
    ('insert into man(manname,manpy,ManLogo) values(:manname,:manpy,:ManLogo)');
  DataModule2.FDQsaveman.Parameters.ParamByName('manname').Value := manname;
  DataModule2.FDQsaveman.Parameters.ParamByName('manpy').Value := manpy;
  TBlobField(DataModule2.FDQsaveman.Parameters.ParamByName('ManLogo'))
    .Assign(manlogo);
  // DataModule2.FDQman.Params.ParamByName('IsNative').Value:= 1;
  DataModule2.FDQsaveman.ExecSQL;

end;

procedure TForm1.saveveh;
var
  stra, strf, strr: string;
  strav, strfv, strrv: string;
begin
  { DataModule2.FDQveh.SQL.Clear;
    DataModule2.FDQveh.SQL.Add('insert into vehicle(ManName,ManPy,ModelName,'+
    'ModelPy,BeginDT,EndDT,WheelBase,TrackDia,FTreadWidth,RTreadWidth,'+
    'KpiCasterMin,KpiCaster,kpicastermax,KpiCastertMin,KpiCastert,KpiCastertMax,'+
    'KpiCamberMin,KpiCamber,KpiCamberMax,KpiCambertMin,KpiCambert,KpiCambertMax)'+
    ' values(:ManName,:ManPy,:ModelName,:ModelPy,:BeginDT,:EndDT,:WheelBase,'+
    ':TrackDia,:FTreadWidth,:RTreadWidth,:KpiCasterMin,:KpiCaster,:kpicastermax,'+
    ':KpiCastertMin,:KpiCastert,:KpiCastertMax,:KpiCamberMin,:KpiCamber,'+
    ':KpiCamberMax,:KpiCambertMin,:KpiCambert,:KpiCambertMax)');
    DataModule2.FDQveh.Params.ParamByName('ManName').Value:= vehpara.ManName;
    DataModule2.FDQveh.Params.ParamByName('ManPy').Value:= vehpara.ManPy;
    DataModule2.FDQveh.Params.ParamByName('ModelName').Value:= vehpara.ModelName;
    DataModule2.FDQveh.Params.ParamByName('ModelPy').Value:= vehpara.ModelPy;
    DataModule2.FDQveh.Params.ParamByName('BeginDT').Value:= vehpara.BeginDT;
    DataModule2.FDQveh.Params.ParamByName('EndDT').Value:= vehpara.EndDT;
    DataModule2.FDQveh.Params.ParamByName('WheelBase').Value:= vehpara.WheelBase;
    DataModule2.FDQveh.Params.ParamByName('TrackDia').Value:= vehpara.TrackDia;
    DataModule2.FDQveh.Params.ParamByName('FTreadWidth').Value:= vehpara.FTreadWidth;
    DataModule2.FDQveh.Params.ParamByName('RTreadWidth').Value:= vehpara.RTreadWidth;
    DataModule2.FDQveh.Params.ParamByName('KpiCasterMin').Value:= vehpara.KpiCasterMin;
    DataModule2.FDQveh.Params.ParamByName('KpiCaster').Value:= vehpara.KpiCaster;

    DataModule2.FDQveh.Params.ParamByName('kpicastermax').Value:= vehpara.kpicastermax;
    DataModule2.FDQveh.Params.ParamByName('KpiCastertMin').Value:= vehpara.KpiCastertMin;
    DataModule2.FDQveh.Params.ParamByName('KpiCastert').Value:= vehpara.KpiCastert;
    DataModule2.FDQveh.Params.ParamByName('KpiCastertMax').Value:= vehpara.KpiCastertMax;
    DataModule2.FDQveh.Params.ParamByName('KpiCamberMin').Value:= vehpara.KpiCamberMin;
    DataModule2.FDQveh.Params.ParamByName('KpiCamber').Value:= vehpara.KpiCamber;

    DataModule2.FDQveh.Params.ParamByName('KpiCamberMax').Value:= vehpara.KpiCamberMax;
    DataModule2.FDQveh.Params.ParamByName('KpiCambertMin').Value:= vehpara.KpiCambertMin;
    DataModule2.FDQveh.Params.ParamByName('KpiCambert').Value:= vehpara.KpiCambert;
    DataModule2.FDQveh.Params.ParamByName('KpiCambertMax').Value:= vehpara.KpiCambertMax;
    DataModule2.FDQveh.ExecSQL; }
  DataModule2.FDQveh.SQL.Clear;
  stra := 'ManName,ManPy,ModelName,ModelPy,BeginDT,EndDT,WheelBase,TrackDia,FTreadWidth,RTreadWidth,'
    + 'KpiCasterMin,KpiCaster,kpicastermax,KpiCastertMin,KpiCastert,KpiCastertMax,'
    + 'KpiCamberMin,KpiCamber,KpiCamberMax,KpiCambertMin,KpiCambert,KpiCambertMax';
  strf := ',FToeMin,fToe,fToeMax,ftoetmin,ftoetmax,FToeSumMin,ftoesum,FToeSumMax,FToesumTmin,FToesumTmax,'
    + 'FCamberMin,FCamber,FCamberMax,FCamberTmin,FCamberT,FCamberTmax,' +
    'FBackMin,FBack,FBackMax';
  strr := ',RToeMin,RToe,RToeMax,RToetMin,RToeT,RToetMax,RToeSumMin,RToeSum,RToeSumMax,RToeSumtMin,'
    + 'RToeSumtMax,RCamberMin,RCamber,RCamberMax,RCambertMin,RCamberT,' +
    'RCambertMax,RBackMin,RBack,RBackMax,RThrustMin,RThrust,RThrustMax,ftoemovie,rtoemovie';
  // ftoemovie,rtoemovie 分别为录入修改人及修改时间

  strav := ':ManName,:ManPy,:ModelName,:ModelPy,:BeginDT,:EndDT,:WheelBase,' +
    ':TrackDia,:FTreadWidth,:RTreadWidth,:KpiCasterMin,:KpiCaster,:kpicastermax,'
    + ':KpiCastertMin,:KpiCastert,:KpiCastertMax,:KpiCamberMin,:KpiCamber,' +
    ':KpiCamberMax,:KpiCambertMin,:KpiCambert,:KpiCambertMax';
  strfv := ',:FToeMin,:fToe,:fToeMax,:ftoetmin,:ftoetmax,:FToeSumMin,:ftoesum,'
    + ':FToeSumMax,:FToesumTmin,:FToesumTmax,:FCamberMin,:FCamber,:FCamberTmin,'
    + ':FCamberT,:FCamberTmax,:FBackMin,:FBack,:FCamberMax,' + ':FBackMax';
  strrv := ',:RToeMin,:RToe,:RToeMax,:RToetMin,:RToeT,:RToetMax,:RToeSumMin,' +
    ':RToeSum,:RToeSumMax,:RToeSumtMin,:RToeSumtMax,:RCamberMin,:RCamber,' +
    ':RCamberMax,:RCambertMin,:RCamberT,:RCambertMax,:RBackMin,' +
    ':RBack,:RBackMax,:RThrustMin,:RThrust,:RThrustMax,:ftoemovie,:rtoemovie';
  DataModule2.FDQveh.SQL.Add('insert into vehicle(' + stra + strf + strr + ')' +
    ' values(' + strav + strfv + strrv + ')');
  DataModule2.FDQveh.Parameters.ParamByName('ManName').Value := vehpara.manname;
  DataModule2.FDQveh.Parameters.ParamByName('ManPy').Value := vehpara.manpy;
  DataModule2.FDQveh.Parameters.ParamByName('ModelName').Value :=
    vehpara.ModelName;
  DataModule2.FDQveh.Parameters.ParamByName('ModelPy').Value := vehpara.ModelPy;
  DataModule2.FDQveh.Parameters.ParamByName('BeginDT').Value := vehpara.BeginDT;
  DataModule2.FDQveh.Parameters.ParamByName('EndDT').Value := vehpara.EndDT;
  DataModule2.FDQveh.Parameters.ParamByName('WheelBase').Value :=
    vehpara.WheelBase;
  DataModule2.FDQveh.Parameters.ParamByName('TrackDia').Value :=
    vehpara.TrackDia;
  DataModule2.FDQveh.Parameters.ParamByName('FTreadWidth').Value :=
    vehpara.FTreadWidth;
  DataModule2.FDQveh.Parameters.ParamByName('RTreadWidth').Value :=
    vehpara.RTreadWidth;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCasterMin').Value :=
    vehpara.KpiCasterMin;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCaster').Value :=
    vehpara.KpiCaster;

  DataModule2.FDQveh.Parameters.ParamByName('kpicastermax').Value :=
    vehpara.KpiCasterMax;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCastertMin').Value :=
    vehpara.KpiCastertMin;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCastert').Value :=
    vehpara.KpiCasterT;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCastertMax').Value :=
    vehpara.KpiCastertMax;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCamberMin').Value :=
    vehpara.KpiCamberMin;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCamber').Value :=
    vehpara.KpiCamber;

  DataModule2.FDQveh.Parameters.ParamByName('KpiCamberMax').Value :=
    vehpara.KpiCamberMax;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCambertMin').Value :=
    vehpara.KpiCambertMin;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCambert').Value :=
    vehpara.KpiCamberT;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCambertMax').Value :=
    vehpara.KpiCambertMax;
  // DataModule2.FDQveh.ExecSQL;

end;

procedure TForm1.savevehf;
begin
  // DataModule2.FDQveh.SQL.Clear;
  { DataModule2.FDQveh.SQL.Add('insert into vehicle(FToeMin,fToe,fToeMax,'+
    'ftoetmin,ftoetmax,FToeSumMin,ftoesum,FToeSumMax,FToesumTmin,FToesumTmax,'+
    'FCamberMin,FCamber,FCamberMax,FCamberTmin,FCamberT,FCamberTmax,'+
    'FBackMin,FBack,FBackMax)'+
    ' values(:FToeMin,:fToe,:fToeMax,:ftoetmin,:ftoetmax,:FToeSumMin,:ftoesum,'+
    ':FToeSumMax,:FToesumTmin,:FToesumTmax,:FCamberMin,:FCamber,:FCamberTmin,'+
    ':FCamberT,:FCamberTmax,:FBackMin,:FBack,:FCamberMax,'+
    ':FBackMax)'); }
  DataModule2.FDQveh.Parameters.ParamByName('FToeMin').Value := vehpara.FToeMin;
  DataModule2.FDQveh.Parameters.ParamByName('fToe').Value := vehpara.FToe;
  DataModule2.FDQveh.Parameters.ParamByName('fToeMax').Value := vehpara.FToeMax;
  DataModule2.FDQveh.Parameters.ParamByName('ftoetmin').Value :=
    vehpara.FToeTmin;
  DataModule2.FDQveh.Parameters.ParamByName('ftoetmax').Value :=
    vehpara.FToeTmax;
  DataModule2.FDQveh.Parameters.ParamByName('FToeSumMin').Value :=
    vehpara.FToeSumMin;
  DataModule2.FDQveh.Parameters.ParamByName('ftoesum').Value := vehpara.FToeSum;
  DataModule2.FDQveh.Parameters.ParamByName('FToeSumMax').Value :=
    vehpara.FToeSumMax;
  DataModule2.FDQveh.Parameters.ParamByName('FToesumTmin').Value :=
    vehpara.FToesumTmin;
  DataModule2.FDQveh.Parameters.ParamByName('FToesumTmax').Value :=
    vehpara.FToesumTmax;
  DataModule2.FDQveh.Parameters.ParamByName('FCamberMin').Value :=
    vehpara.FCamberMin;
  DataModule2.FDQveh.Parameters.ParamByName('FCamber').Value := vehpara.FCamber;

  DataModule2.FDQveh.Parameters.ParamByName('FCamberMax').Value :=
    vehpara.FCamberMax;
  DataModule2.FDQveh.Parameters.ParamByName('FCamberTmin').Value :=
    vehpara.FCamberTmin;
  DataModule2.FDQveh.Parameters.ParamByName('FCamberT').Value :=
    vehpara.FCamberT;
  DataModule2.FDQveh.Parameters.ParamByName('FCamberTmax').Value :=
    vehpara.FCamberTmax;
  DataModule2.FDQveh.Parameters.ParamByName('FBackMin').Value :=
    vehpara.FBackMin;
  DataModule2.FDQveh.Parameters.ParamByName('FBack').Value := vehpara.FBack;

  DataModule2.FDQveh.Parameters.ParamByName('FBackMax').Value :=
    vehpara.FBackMax;
  // DataModule2.FDQveh.ExecSQL;
end;

procedure TForm1.savevehr;
begin
  // DataModule2.FDQveh.SQL.Clear;
  { DataModule2.FDQveh.SQL.Add('insert into vehicle(RToeMin,RToe,RToeMax,'+
    'RToetMin,RToeT,RToetMax,RToeSumMin,RToeSum,RToeSumMax,RToeSumtMin,'+
    'RToeSumtMax,RCamberMin,RCamber,RCamberMax,RCambertMin,RCamberT,'+
    'RCambertMax,RBackMin,RBack,RBackMax,RThrustMin,RThrust,RThrustMax)'+
    ' values(:RToeMin,:RToe,:RToeMax,:RToetMin,:RToeT,:RToetMax,:RToeSumMin,'+
    ':RToeSum,:RToeSumMax,:RToeSumtMin,:RToeSumtMax,:RCamberMin,:RCamber,'+
    ':RCamberMax,:RCambertMin,:RCamberT,:RCambertMax,:RBackMin,'+
    ':RBack,:RBackMax,:RThrustMin,:RThrust,:RThrustMax)'); }
  DataModule2.FDQveh.Parameters.ParamByName('RToeMin').Value := vehpara.RToeMin;
  DataModule2.FDQveh.Parameters.ParamByName('RToe').Value := vehpara.RToe;
  DataModule2.FDQveh.Parameters.ParamByName('RToeMax').Value := vehpara.RToeMax;
  DataModule2.FDQveh.Parameters.ParamByName('RToetMin').Value :=
    vehpara.RToetMin;
  DataModule2.FDQveh.Parameters.ParamByName('RToeT').Value := vehpara.RToeT;
  DataModule2.FDQveh.Parameters.ParamByName('RToetMax').Value :=
    vehpara.RToetMax;
  DataModule2.FDQveh.Parameters.ParamByName('RToeSumMin').Value :=
    vehpara.RToeSumMin;
  DataModule2.FDQveh.Parameters.ParamByName('RToeSum').Value := vehpara.RToeSum;
  DataModule2.FDQveh.Parameters.ParamByName('RToeSumMax').Value :=
    vehpara.RToeSumMax;
  DataModule2.FDQveh.Parameters.ParamByName('RToeSumtMin').Value :=
    vehpara.RToeSumtMin;
  DataModule2.FDQveh.Parameters.ParamByName('RToeSumtMax').Value :=
    vehpara.RToeSumtMax;
  DataModule2.FDQveh.Parameters.ParamByName('RCamberMin').Value :=
    vehpara.RCamberMin;

  DataModule2.FDQveh.Parameters.ParamByName('RCamber').Value := vehpara.RCamber;
  DataModule2.FDQveh.Parameters.ParamByName('RCamberMax').Value :=
    vehpara.RCamberMax;
  DataModule2.FDQveh.Parameters.ParamByName('RCambertMin').Value :=
    vehpara.RCambertMin;
  DataModule2.FDQveh.Parameters.ParamByName('RCamberT').Value :=
    vehpara.RCamberT;
  DataModule2.FDQveh.Parameters.ParamByName('RCambertMax').Value :=
    vehpara.RCambertMax;
  DataModule2.FDQveh.Parameters.ParamByName('RBackMin').Value :=
    vehpara.RBackMin;

  DataModule2.FDQveh.Parameters.ParamByName('RBack').Value := vehpara.RBack;
  DataModule2.FDQveh.Parameters.ParamByName('RBackMax').Value :=
    vehpara.RBackMax;
  DataModule2.FDQveh.Parameters.ParamByName('RThrustMin').Value :=
    vehpara.RThrustMin;
  DataModule2.FDQveh.Parameters.ParamByName('RThrust').Value := vehpara.RThrust;
  DataModule2.FDQveh.Parameters.ParamByName('RThrustMax').Value :=
    vehpara.RThrustMax;
  DataModule2.FDQveh.Parameters.ParamByName('ftoemovie').Value := loginname;
  // 录入人
  DataModule2.FDQveh.Parameters.ParamByName('rtoemovie').Value :=
    formatdatetime('yyyy-mm-dd hh:mm:ss', now); // 时间录入
  // ftoemovie,rtoemovie
  DataModule2.FDQveh.ExecSQL;
end;

procedure TForm1.updateveh;
begin
  DataModule2.FDQveh.SQL.Clear;
  DataModule2.FDQveh.SQL.Add('update vehicle set ManPy=:ManPy,' +
    'ModelPy=:ModelPy,BeginDT=:BeginDT,EndDT=:EndDT,WheelBase=:WheelBase,TrackDia=:TrackDia,'
    + 'FTreadWidth=:FTreadWidth,RTreadWidth=:RTreadWidth,KpiCasterMin=:KpiCasterMin,KpiCaster=:KpiCaster,'
    + 'kpicastermax=:kpicastermax,KpiCastertMin=:KpiCastertMin,KpiCastert=:KpiCastert,KpiCastertMax=:KpiCastertMax,'
    + 'KpiCamberMin=:KpiCamberMin,KpiCamber=:KpiCamber,KpiCamberMax=:KpiCamberMax,'
    + 'KpiCambertMin=:KpiCambertMin,KpiCambert=:KpiCambert,KpiCambertMax=:KpiCambertMax'
    + ' where ManName=' + quotedstr(vehpara.manname) + ' and ModelName=' +
    quotedstr(vehpara.ModelName));
  DataModule2.FDQveh.Parameters.ParamByName('ManPy').Value := vehpara.manpy;
  DataModule2.FDQveh.Parameters.ParamByName('ModelPy').Value := vehpara.ModelPy;
  DataModule2.FDQveh.Parameters.ParamByName('BeginDT').Value := vehpara.BeginDT;
  DataModule2.FDQveh.Parameters.ParamByName('EndDT').Value := vehpara.EndDT;
  DataModule2.FDQveh.Parameters.ParamByName('WheelBase').Value :=
    vehpara.WheelBase;
  DataModule2.FDQveh.Parameters.ParamByName('TrackDia').Value :=
    vehpara.TrackDia;
  DataModule2.FDQveh.Parameters.ParamByName('FTreadWidth').Value :=
    vehpara.FTreadWidth;
  DataModule2.FDQveh.Parameters.ParamByName('RTreadWidth').Value :=
    vehpara.RTreadWidth;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCasterMin').Value :=
    vehpara.KpiCasterMin;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCaster').Value :=
    vehpara.KpiCaster;
  DataModule2.FDQveh.Parameters.ParamByName('kpicastermax').Value :=
    vehpara.KpiCasterMax;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCastertMin').Value :=
    vehpara.KpiCastertMin;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCastert').Value :=
    vehpara.KpiCasterT;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCastertMax').Value :=
    vehpara.KpiCastertMax;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCamberMin').Value :=
    vehpara.KpiCamberMin;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCamber').Value :=
    vehpara.KpiCamber;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCamberMax').Value :=
    vehpara.KpiCamberMax;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCambertMin').Value :=
    vehpara.KpiCambertMin;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCambert').Value :=
    vehpara.KpiCamberT;
  DataModule2.FDQveh.Parameters.ParamByName('KpiCambertMax').Value :=
    vehpara.KpiCambertMax;
  DataModule2.FDQveh.ExecSQL;
end;

procedure TForm1.updatevehf;
begin
  DataModule2.FDQveh.SQL.Clear;
  DataModule2.FDQveh.SQL.Add('update vehicle set FToeMin=:FToeMin,' +
    'FToe=:FToe,FToeMax=:FToeMax,ftoetmin=:ftoetmin,ftoetmax=:ftoetmax,FToeSumMin=:FToeSumMin,'
    + 'ftoesum=:ftoesum,FToeSumMax=:FToeSumMax,FToesumTmin=:FToesumTmin,FToesumTmax=:FToesumTmax,'
    + 'FCamberMin=:FCamberMin,FCamber=:FCamber,FCamberMax=:FCamberMax,FCamberTmin=:FCamberTmin,'
    + 'FCamberT=:FCamberT,FCamberTmax=:FCamberTmax,FBackMin=:FBackMin,' +
    'FBack=:FBack,FBackMax=:FBackMax' + ' where ManName=' +
    quotedstr(vehpara.manname) + ' and ModelName=' +
    quotedstr(vehpara.ModelName));
  DataModule2.FDQveh.Parameters.ParamByName('FToeMin').Value := vehpara.FToeMin;
  DataModule2.FDQveh.Parameters.ParamByName('FToe').Value := vehpara.FToe;
  DataModule2.FDQveh.Parameters.ParamByName('FToeMax').Value := vehpara.FToeMax;
  DataModule2.FDQveh.Parameters.ParamByName('ftoetmin').Value :=
    vehpara.FToeTmin;
  DataModule2.FDQveh.Parameters.ParamByName('ftoetmax').Value :=
    vehpara.FToeTmax;
  DataModule2.FDQveh.Parameters.ParamByName('FToeSumMin').Value :=
    vehpara.FToeSumMin;
  DataModule2.FDQveh.Parameters.ParamByName('FToeSumMax').Value :=
    vehpara.FToeSumMax;
  DataModule2.FDQveh.Parameters.ParamByName('FToeSum').Value := vehpara.FToeSum;
  DataModule2.FDQveh.Parameters.ParamByName('FToeSumtMin').Value :=
    vehpara.FToesumTmin;
  DataModule2.FDQveh.Parameters.ParamByName('FToesumTmax').Value :=
    vehpara.FToesumTmax;
  DataModule2.FDQveh.Parameters.ParamByName('FCamberMin').Value :=
    vehpara.FCamberMin;
  DataModule2.FDQveh.Parameters.ParamByName('FCamber').Value := vehpara.FCamber;
  DataModule2.FDQveh.Parameters.ParamByName('FCamberMax').Value :=
    vehpara.FCamberMax;
  DataModule2.FDQveh.Parameters.ParamByName('FCamberTmin').Value :=
    vehpara.FCamberTmin;
  DataModule2.FDQveh.Parameters.ParamByName('FCamberT').Value :=
    vehpara.FCamberT;
  DataModule2.FDQveh.Parameters.ParamByName('FCamberTmax').Value :=
    vehpara.FCamberTmax;
  DataModule2.FDQveh.Parameters.ParamByName('FBackMin').Value :=
    vehpara.FBackMin;
  DataModule2.FDQveh.Parameters.ParamByName('FBack').Value := vehpara.FBack;
  DataModule2.FDQveh.Parameters.ParamByName('FBackMax').Value :=
    vehpara.FBackMax;

  DataModule2.FDQveh.ExecSQL;
end;

procedure TForm1.updatevehr;
begin
  DataModule2.FDQveh.SQL.Clear;
  DataModule2.FDQveh.SQL.Add('update vehicle set RToeMin=:RToeMin,' +
    'RToe=:RToe,rToeMax=:rToeMax,rtoetmin=:rtoetmin,rtoetmax=:rtoetmax,rToeSumMin=:rToeSumMin,'
    + 'rtoesum=:rtoesum,rToeSumMax=:rToeSumMax,rToesumTmin=:rToesumTmin,rToesumTmax=:rToesumTmax,'
    + 'rCamberMin=:rCamberMin,rCamber=:rCamber,rCamberMax=:rCamberMax,rCamberTmin=:rCamberTmin,'
    + 'rCamberT=:rCamberT,rCamberTmax=:rCamberTmax,rBackMin=:rBackMin,ftoemovie=:ftoemovie,rtoemovie=:rtoemovie,'
    + 'rBack=:rBack,rBackMax=:rBackMax,RToeT=:RToeT,RThrustMin=:RThrustMin,RThrust=:RThrust,RThrustMax=:RThrustMax'
    + ' where ManName=' + quotedstr(vehpara.manname) + ' and ModelName=' +
    quotedstr(vehpara.ModelName));
  DataModule2.FDQveh.Parameters.ParamByName('RToeMin').Value := vehpara.RToeMin;
  DataModule2.FDQveh.Parameters.ParamByName('RToe').Value := vehpara.RToe;
  DataModule2.FDQveh.Parameters.ParamByName('rToeMax').Value := vehpara.RToeMax;
  DataModule2.FDQveh.Parameters.ParamByName('rtoetmin').Value :=
    vehpara.RToetMin;
  DataModule2.FDQveh.Parameters.ParamByName('rtoetmax').Value :=
    vehpara.RToetMax;
  DataModule2.FDQveh.Parameters.ParamByName('rToeSumMin').Value :=
    vehpara.RToeSumMin;
  DataModule2.FDQveh.Parameters.ParamByName('rtoesum').Value := vehpara.RToeSum;
  ///
  DataModule2.FDQveh.Parameters.ParamByName('rToeSumMax').Value :=
    vehpara.RToeSumMax;
  DataModule2.FDQveh.Parameters.ParamByName('rToesumTmin').Value :=
    vehpara.RToeSumtMin;
  DataModule2.FDQveh.Parameters.ParamByName('rToesumTmax').Value :=
    vehpara.RToeSumtMax;
  DataModule2.FDQveh.Parameters.ParamByName('rCamberMin').Value :=
    vehpara.RCamberMin;
  DataModule2.FDQveh.Parameters.ParamByName('rCamber').Value := vehpara.RCamber;
  DataModule2.FDQveh.Parameters.ParamByName('rCamberMax').Value :=
    vehpara.RCamberMax;
  DataModule2.FDQveh.Parameters.ParamByName('rCamberTmin').Value :=
    vehpara.RCambertMin;
  DataModule2.FDQveh.Parameters.ParamByName('rCamberT').Value :=
    vehpara.RCamberT;
  DataModule2.FDQveh.Parameters.ParamByName('rCamberTmax').Value :=
    vehpara.RCambertMax;
  DataModule2.FDQveh.Parameters.ParamByName('rBackMin').Value :=
    vehpara.RBackMin;
  DataModule2.FDQveh.Parameters.ParamByName('rBack').Value := vehpara.RBack;
  DataModule2.FDQveh.Parameters.ParamByName('rBackMax').Value :=
    vehpara.RBackMax;
  DataModule2.FDQveh.Parameters.ParamByName('RToeT').Value := vehpara.RToeT;
  DataModule2.FDQveh.Parameters.ParamByName('RThrustMin').Value :=
    vehpara.RThrustMin;
  DataModule2.FDQveh.Parameters.ParamByName('RThrust').Value := vehpara.RThrust;
  DataModule2.FDQveh.Parameters.ParamByName('RThrustMax').Value :=
    vehpara.RThrustMax;
  DataModule2.FDQveh.Parameters.ParamByName('ftoemovie').Value := loginname;
  // 修改人
  DataModule2.FDQveh.Parameters.ParamByName('rtoemovie').Value :=
    formatdatetime('yyyy-mm-dd hh:mm:ss', now); // 修改时间
  DataModule2.FDQveh.ExecSQL;
end;

end.
