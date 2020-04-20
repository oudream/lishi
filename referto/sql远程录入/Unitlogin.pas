unit Unitlogin;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes, System.Variants, 
  FMX.Types, FMX.Graphics, FMX.Controls, FMX.Forms, FMX.Dialogs, FMX.StdCtrls,
  FMX.Edit, Data.DB, Data.Win.ADODB;

type
  TForm3 = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Editpass: TEdit;
    Button1: TButton;
    Button2: TButton;
    Laberror: TLabel;
    ADOQcust: TADOQuery;
    ADOConnection1: TADOConnection;
    Editname: TComboEdit;
    procedure Button2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form3: TForm3;

implementation
uses unit2,unit1;
{$R *.fmx}
var
 FnameFile:textFile;
 FFileName: string;
 fExists:boolean;
procedure TForm3.Button1Click(Sender: TObject);
var
strname,strpass:string;
lst:TStringList ;
begin
//�������ݿ�Ƚ��û�������
strname:=trim(Editname.text);
strpass:=trim(Editpass.Text);
loginname:=strname;
loginok:=false;
ADOQcust.Active:=false;
ADOQcust.SQL.Clear;
ADOQcust.SQL.Add('select custname from customer where custname='
+quotedstr(strname)+' and custpass='+quotedstr(strpass));
ADOQcust.Active:=true;
if ADOQcust.RecordCount=0 then
  begin
    //�û��������
   Laberror.Visible:=true;
  end
  else
  begin
    if fExists then
    begin
      lst:=TStringList.Create ;
    try
      lst.LoadFromFile(FFileName);
      if lst.IndexOf(strname)=0 then
      begin
        // �����½��
        AssignFile(FnameFile,FFileName);
        Append(FnameFile);  //��׼��׷��
        Writeln(FnameFile, strname);
        CloseFile(FnameFile);
      end;
     finally
       lst.Free ;
     end;
    end
    else
    begin
      // �����½��
        AssignFile(FnameFile,FFileName);
        Rewrite(FnameFile);  //����
        Writeln(FnameFile, strname);
        CloseFile(FnameFile);
    end;
   loginok:=true;
  // Laberror.Text:='��������Զ�����ݿ⣬���Ժ�...';
   self.Close;
    //��½ �ɹ�

  end;

end;

procedure TForm3.Button2Click(Sender: TObject);
begin
application.Terminate;
end;

procedure TForm3.FormCreate(Sender: TObject);
begin
  FFileName:=extractfilepath(paramstr(0))+'lslogin.ini';
  if FileExists(FFileName) then
  begin
    fExists:=true;
    editname.Items.LoadFromFile(FFileName);
  end;
end;

procedure TForm3.FormShow(Sender: TObject);
begin
//��ȡini�ļ���ȡ�û���

end;

end.
