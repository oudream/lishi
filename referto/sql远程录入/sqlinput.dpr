program sqlinput;

uses
  FMX.Forms,
  Unit1 in 'Unit1.pas' {Form1},
  Unit2 in 'Unit2.pas' {DataModule2: TDataModule},
  Unitlogin in 'Unitlogin.pas' {Form3};

{$R *.res}
var
frmlogin:tform3;
begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TDataModule2, DataModule2);
  frmlogin:=tform3.Create(application);
  frmlogin.ShowModal;
  frmlogin.Free;
  Application.Run;

end.
