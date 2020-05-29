%%% �������� ������� ��
function GAResult=gaLocal(InputParams) 
%% �������������
% �������� �� ������� ���������
if nargin==1
    GAResult=InputParams;
else
    error('Error: no input params')
end

%% ��������� �������� ��-���������, ���� �� ������ �� ��. ������
% ����������� ������������
if ~isfield(GAResult,'DimensionSpace')
    % � ������ ���������� ������������, ��� ���������� �������� �������
    GAResult.DimensionSpace=size(GAResult.SpaceIntervals,2);
end
% ������ ��������� (����� ������)
if ~isfield(GAResult,'SizeOfPopulation')
    GAResult.SizeOfPopulation=GAResult.NVAR*50;
end
% ���������� ��������� (���������)
if ~isfield(GAResult,'NumOfIterations')
    GAResult.NumOfIterations=GAResult.NVAR*20+10;
end
% ����������� ������������� (�����������)
if ~isfield(GAResult,'Pc')
    GAResult.Pc=0.5;
end
% ����������� �������
if ~isfield(GAResult,'Pm')
    GAResult.Pm=0.1;
end
% ��������� ��� ��������������� ���������� (�������� [0,1])
if ~isfield(GAResult,'Alpha')
    GAResult.Alpha=0.5;
end

%% ������������� ���������� ����������
% ��������� � ������� ��������
GAResult.Population=[];
% �������� �������� ������� � ������� ��������
GAResult.FuncValues=[];
% ����������� �������� ���������� ������� � ������� ��������
GAResult.Xmin=[];
% ����������� �������� ������� � ������� ��������
GAResult.Fxmin=inf;
% ����������� �������� ���������� ������� �� ������ ��������
GAResult.XminGen=[];
% ����������� �������� ������� �� ������ ��������
GAResult.FxminGen=[];
% ������� ����� ���������
GAResult.Generation=0;

%% ������ ������ ���������
% ������� ���������
CurrentGeneration=0;
% ��������� ��������� ���������
GAResult.Population=createRandPopulation(GAResult.SizeOfPopulation,GAResult.SpaceIntervals);  

% ������� ���� ���������
while (GAResult.Generation<GAResult.NumOfIterations)
    GAResult.Generation=CurrentGeneration;
    GAResult=performGAIteration(GAResult);     
    GAResult.XminGen(CurrentGeneration+1,:)=GAResult.Xmin;
    GAResult.FxminGen(CurrentGeneration+1,:)=GAResult.Fxmin;
    CurrentGeneration=CurrentGeneration+1;
end
