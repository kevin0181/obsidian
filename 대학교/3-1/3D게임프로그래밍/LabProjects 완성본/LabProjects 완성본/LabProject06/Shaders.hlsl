struct VS_INPUT		//���� ���̴��� �Է��� ���� ����ü�� �����Ѵ�.
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT	//���� ���̴��� ���(�ȼ� ���̴��� �Է�)�� ���� ����ü�� �����Ѵ�.
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VS_OUTPUT VSMain(VS_INPUT input) //���� ���̴��� �����Ѵ�.
{
	VS_OUTPUT output;
	output.position = float4(input.position, 1.0f);   //������ ��ġ ���ʹ� ������ǥ��� ǥ���Ǿ� �����Ƿ� ��ȯ���� �ʰ� �״�� ����Ѵ�. 
	output.color = input.color;						  //�ԷµǴ� �ȼ��� ����(�����Ͷ����� �ܰ迡�� �����Ͽ� ���� ����)�� �״�� ����Ѵ�. 
	return(output);
}

float4 PSMain(VS_OUTPUT input) : SV_TARGET //�ȼ� ���̴��� �����Ѵ�.
{
   return(input.color); //�ԷµǴ� �ȼ��� ������ �״�� ���-���� �ܰ�(���� Ÿ��)�� ����Ѵ�. 
}