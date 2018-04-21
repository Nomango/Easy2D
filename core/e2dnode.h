#pragma once
#include "e2dbase.h"

namespace e2d 
{


class Action;
class Transition;
class Collider;
class ColliderManager;

class Node :
	public Object
{
	friend Scene;
	friend Collider;
	friend Transition;
	friend ColliderManager;

public:
	Node();

	virtual ~Node();

	// ���볡��ʱִ��
	virtual void onEnter() {}

	// �뿪����ʱִ��
	virtual void onExit() {}

	// ���½ڵ�
	virtual void onUpdate() {}

	// �̶��ظ��£���Ϸ��ͣʱ��Ȼ���У�
	virtual void onFixedUpdate() {}

	// ��Ⱦ�ڵ�
	virtual void onRender() {}

	// ��ײ����
	virtual void onCollide(
		Node* pNode	/* ������ײ�Ľڵ� */
	) {}

	// ��ȡ�ڵ���ʾ״̬
	virtual bool isVisiable() const;

	// �жϵ��Ƿ��ڽڵ���
	virtual bool isPointIn(
		Point point
	) const;

	// �ж����ڵ��Ƿ��ཻ
	virtual bool isIntersectWith(
		const Node * pNode
	) const;

	// ��ȡ�ڵ�����
	virtual String getName() const;

	// ��ȡ�ڵ����Ƶ� Hash ֵ
	virtual unsigned int getHashName() const;

	// ��ȡ�ڵ��ͼ˳��
	virtual int getOrder() const;

	// ��ȡ�ڵ������
	virtual double getPosX() const;

	// ��ȡ�ڵ�������
	virtual double getPosY() const;

	// ��ȡ�ڵ�����
	virtual Point getPos() const;

	// ��ȡ�ڵ����
	virtual double getWidth() const;

	// ��ȡ�ڵ�߶�
	virtual double getHeight() const;

	// ��ȡ�ڵ���ȣ����������ţ�
	virtual double getRealWidth() const;

	// ��ȡ�ڵ�߶ȣ����������ţ�
	virtual double getRealHeight() const;

	// ��ȡ�ڵ��С�����������ţ�
	virtual Size getRealSize() const;

	// ��ȡ�ڵ�����ĵ�
	virtual double getPivotX() const;

	// ��ȡ�ڵ�����ĵ�
	virtual double getPivotY() const;

	// ��ȡ�ڵ��С
	virtual Size getSize() const;

	// ��ȡ�ڵ�������ű���
	virtual double getScaleX() const;

	// ��ȡ�ڵ��������ű���
	virtual double getScaleY() const;

	// ��ȡ�ڵ������б�Ƕ�
	virtual double getSkewX() const;

	// ��ȡ�ڵ�������б�Ƕ�
	virtual double getSkewY() const;

	// ��ȡ�ڵ���ת�Ƕ�
	virtual double getRotation() const;

	// ��ȡ�ڵ�͸����
	virtual double getOpacity() const;

	// ��ȡ�ڵ�����
	virtual NodeProperty getProperty() const;

	// ��ȡ�ڵ���ײ��
	virtual Collider * getCollider() const;

	// ��ȡ���ڵ�
	virtual Node * getParent() const;

	// ��ȡ�ڵ����ڳ���
	virtual Scene * getParentScene() const;

	// ��ȡ����������ͬ���ӽڵ�
	virtual std::vector<Node*> getChildren(
		String name
	);

	// ��ȡ�����ӽڵ�
	virtual std::vector<Node*> getChildren();

	// ��ȡ�ӽڵ�����
	virtual int getChildrenCount() const;

	// �Ƴ��ӽڵ�
	virtual bool removeChild(
		Node * child
	);

	// �Ƴ�����������ͬ���ӽڵ�
	virtual void removeChildren(
		String childName
	);

	// �Ӹ��ڵ��Ƴ�
	virtual void removeFromParent();

	// �Ƴ����нڵ�
	virtual void clearAllChildren();

	// ���ýڵ��Ƿ���ʾ
	virtual void setVisiable(
		bool value
	);

	// ��������� onUpdate ����
	virtual void setAutoUpdate(
		bool bAutoUpdate
	);

	// ���ýڵ�����
	virtual void setName(
		String name
	);

	// ���ýڵ������
	virtual void setPosX(
		double x
	);

	// ���ýڵ�������
	virtual void setPosY(
		double y
	);

	// ���ýڵ�����
	virtual void setPos(
		const Point & point
	);

	// ���ýڵ�����
	virtual void setPos(
		double x,
		double y
	);

	// �ƶ��ڵ�
	virtual void movePosX(
		double x
	);

	// �ƶ��ڵ�
	virtual void movePosY(
		double y
	);

	// �ƶ��ڵ�
	virtual void movePos(
		double x,
		double y
	);

	// �ƶ��ڵ�
	virtual void movePos(
		const Vector & v
	);

	// ���ýڵ��ͼ˳��
	// Ĭ��Ϊ 0
	virtual void setOrder(
		int order
	);

	// ���ú������ű���
	// Ĭ��Ϊ 1.0f
	virtual void setScaleX(
		double scaleX
	);

	// �����������ű���
	// Ĭ��Ϊ 1.0f
	virtual void setScaleY(
		double scaleY
	);

	// �������ű���
	// Ĭ��Ϊ (1.0f, 1.0f)
	virtual void setScale(
		double scaleX,
		double scaleY
	);

	// �������ű���
	// Ĭ��Ϊ 1.0f
	virtual void setScale(
		double scale
	);

	// ���ú�����б�Ƕ�
	// Ĭ��Ϊ 0
	virtual void setSkewX(
		double angleX
	);

	// ����������б�Ƕ�
	// Ĭ��Ϊ 0
	virtual void setSkewY(
		double angleY
	);

	// ������б�Ƕ�
	// Ĭ��Ϊ (0, 0)
	virtual void setSkew(
		double angleX,
		double angleY
	);

	// ������ת�Ƕ�
	// Ĭ��Ϊ 0
	virtual void setRotation(
		double rotation
	);

	// ����͸����
	// Ĭ��Ϊ 1.0f, ��Χ [0, 1]
	virtual void setOpacity(
		double opacity
	);

	// �������ĵ�ĺ���λ��
	// Ĭ��Ϊ 0, ��Χ [0, 1]
	virtual void setPivotX(
		double pivotX
	);

	// �������ĵ������λ��
	// Ĭ��Ϊ 0, ��Χ [0, 1]
	virtual void setPivotY(
		double pivotY
	);

	// �������ĵ�λ��
	// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
	virtual void setPivot(
		double pivotX,
		double pivotY
	);

	// �޸Ľڵ����
	virtual void setWidth(
		double width
	);

	// �޸Ľڵ�߶�
	virtual void setHeight(
		double height
	);

	// �޸Ľڵ��С
	virtual void setSize(
		double width,
		double height
	);

	// �޸Ľڵ��С
	virtual void setSize(
		Size size
	);

	// ���ýڵ�����
	virtual void setProperty(
		NodeProperty prop
	);

	// ������ײ��
	virtual void setCollider(
		int nColliderType
	);

	// ������ײ��
	virtual void setCollider(
		Collider * pCollider
	);

	// ���ӿ���ײ�ڵ������
	virtual void addColliableName(
		String collliderName
	);

#if HIGHER_THAN_VS2012
	// ���Ӷ������ײ�ڵ������
	virtual void addColliableName(
		const InitList<String>& vCollliderName	/* �������� */
	);
#endif

	// �Ƴ�����ײ�ڵ������
	virtual void removeColliableName(
		String collliderName
	);

	// �����ӽڵ�
	virtual void addChild(
		Node * child,
		int order = 0	/* ��Ⱦ˳�� */
	);

#if HIGHER_THAN_VS2012
	// ���Ӷ���ӽڵ�
	virtual void addChild(
		const InitList<Node*>& vNodes,	/* �ڵ����� */
		int order = 0							/* ��Ⱦ˳�� */
	);
#endif

	// ִ�ж���
	virtual void runAction(
		Action * action
	);

	// ��������
	virtual void resumeAction(
		String strActionName
	);

	// ��ͣ����
	virtual void pauseAction(
		String strActionName
	);

	// ֹͣ����
	virtual void stopAction(
		String strActionName
	);

	// ��ȡ������ͬ�Ķ���
	virtual Action * getAction(
		String strActionName
	);

	// ��ȡ����������ͬ�Ķ���
	virtual std::vector<Action*> getActions(
		String strActionName
	);

	// ����������ͣ����
	virtual void resumeAllActions();

	// ��ͣ���ж���
	virtual void pauseAllActions();

	// ֹͣ���ж���
	virtual void stopAllActions();

	// �޸Ľڵ��Ĭ�����ĵ�λ��
	static void setDefaultPiovt(
		double defaultPiovtX,
		double defaultPiovtY
	);

	// ���ýڵ��Ƿ����Ĭ����ײ�壨Ĭ�ϴ򿪣�
	static void setDefaultColliderEnable(
		bool bEnable
	);

	// ���ٶ���
	virtual void destroy() override;

protected:
	// ���½ڵ�
	void _update();

	// ��Ⱦ�ڵ�
	void _render();

	// ��Ⱦͼ��
	void _drawCollider();

	// �ڵ㱻���ӵ�����ʱ��ִ�г���
	void _onEnter();

	// �ڵ�ӳ�������ʧʱ��ִ�г���
	void _onExit();

	// ���ýڵ����ڳ���
	void _setParentScene(
		Scene * scene
	);

	// ���������ж�ά����任
	void _updateTransform();

	// ���������ӽڵ����
	void _updateChildrenTransform();

	// ���������ӽڵ�͸����
	void _updateChildrenOpacity();

	// ���½ڵ��ά����
	static void _updateTransform(Node * node);

	// ���½ڵ�͸����
	static void _updateOpacity(Node * node);

protected:
	String		m_sName;
	unsigned	m_nHashName;
	float		m_fPosX;
	float		m_fPosY;
	float		m_fWidth;
	float		m_fHeight;
	float		m_fScaleX;
	float		m_fScaleY;
	float		m_fRotation;
	float		m_fSkewAngleX;
	float		m_fSkewAngleY;
	float		m_fDisplayOpacity;
	float		m_fRealOpacity;
	float		m_fPivotX;
	float		m_fPivotY;
	int			m_nOrder;
	bool		m_bVisiable;
	bool		m_bAutoUpdate;
	bool		m_bDisplayedInScene;
	bool		m_bSortChildrenNeeded;
	bool		m_bTransformNeeded;
	Collider *	m_pCollider;
	Scene *		m_pParentScene;
	Node *		m_pParent;
	D2D1::Matrix3x2F		m_MatriInitial;
	D2D1::Matrix3x2F		m_MatriFinal;
	std::set<unsigned int>	m_vColliders;
	std::vector<Node*>		m_vChildren;
};


class Sprite :
	public Node
{
public:
	// ����һ���վ���
	Sprite();

	// �� EImage ���󴴽�����
	Sprite(
		Image * image
	);

	// ���ļ�ͼƬ��������
	Sprite(
		String imageFileName
	);

	// �������鲢�ü�ͼƬ
	Sprite(
		String imageFileName,
		double x,
		double y,
		double width,
		double height
	);

	virtual ~Sprite();

	// �ӱ����ļ�����ͼƬ
	virtual void open(
		String imageFileName
	);
	
	// ����ͼƬ
	virtual void open(
		Image * image
	);

	// ��ͼƬ�ü�Ϊ����
	virtual void crop(
		double x,
		double y,
		double width,
		double height
	);

	// ��ȡ EImage ����
	virtual Image * getImage() const;

	// ��Ⱦ����
	virtual void onRender() override;

	// ���ٶ���
	virtual void destroy() override;

protected:
	Image * m_pImage;
};


class Text :
	public Node
{
public:
	Text();

	Text(
		String text			/* �������� */
	);

	Text(
		TextStyle textStyle	/* ������ʽ */
	);

	Text(
		String text,		/* �������� */
		TextStyle textStyle	/* ������ʽ */
	);

	Text(
		String text,							/* ��������*/
		String fontFamily,						/* ���� */
		double fontSize = 22,					/* �ֺ� */
		UINT32 color = Color::WHITE,			/* ��ɫ */
		UINT32 fontWeight = FontWeight::NORMAL,	/* ��ϸֵ */
		bool italic = false,					/* б�� */
		bool hasUnderline = false,				/* �»��� */
		bool hasStrikethrough = false,			/* ɾ���� */
		bool showOutline = true,				/* ��ʾ��� */
		UINT32 outlineColor = Color::BLACK,		/* �����ɫ */
		UINT32 outlineWidth = 1.0				/* ����߿� */
	);

	virtual ~Text();

	// ��ȡ�ı�
	String getText() const;

	// ��ȡ�ı���ʽ
	TextStyle getTextStyle() const;

	// ��ȡ����
	String getFontFamily() const;

	// ��ȡ��ǰ�ֺ�
	double getFontSize() const;

	// ��ȡ��ǰ�����ϸֵ
	UINT32 getFontWeight() const;

	// ��ȡ������ɫ
	UINT32 getColor() const;

	// ��ȡ�����ɫ
	UINT32 getOutlineColor() const;

	// ��ȡ����߿�
	double getOutlineWidth() const;

	// ��ȡ������ཻ��ʽ
	int getOutlineJoin() const;

	// ��ȡ�ı���ʾ����
	int getLineCount() const;

	// �Ƿ���б��
	bool isItalic() const;

	// �Ƿ���ʾ���
	bool isShowOutline() const;

	// �����ı�
	void setText(
		String text
	);

	// �����ı���ʽ
	void setTextStyle(
		TextStyle pTextStyle
	);

	// ��������
	void setFontFamily(
		String fontFamily
	);

	// �����ֺţ�Ĭ��ֵΪ 22��
	void setFontSize(
		double fontSize
	);

	// ���������ϸֵ��Ĭ��ֵΪ FontWeight::NORMAL��
	void setFontWeight(
		UINT32 textStyleWeight
	);

	// ����������ɫ��Ĭ��ֵΪ Color::WHITE��
	void setColor(
		UINT32 color
	);

	// ��������б�壨Ĭ��ֵΪ false��
	void setItalic(
		bool value
	);

	// �����ı��Զ����еĿ��ȣ�����Ϊ 0 ʱ�ر��Զ����У�Ĭ��Ϊ 0��
	void setWrappingWidth(
		double fWrappingWidth
	);

	// �����м�ࣨĬ��Ϊ 0��
	void setLineSpacing(
		double fLineSpacing
	);

	// ���ö��뷽ʽ��Ĭ��Ϊ TextAlign::LEFT��
	void setAlignment(
		int nAlign
	);

	// �����»��ߣ�Ĭ��ֵΪ false��
	void setUnderline(
		bool hasUnderline
	);

	// ����ɾ���ߣ�Ĭ��ֵΪ false��
	void setStrikethrough(
		bool hasStrikethrough
	);

	// �����Ƿ���ʾ���
	void showOutline(
		bool showOutline
	);

	// ���������ɫ
	void setOutlineColor(
		UINT32 outlineColor
	);

	// ��������߿�
	void setOutlineWidth(
		double outlineWidth
	);

	// ����������ཻ��ʽ
	void setOutlineJoin(
		int outlineJoin
	);

	// ��Ⱦ����
	virtual void onRender() override;

protected:
	// �����Ű�����
	void _reset();

	// �������ָ�ʽ��
	void _createFormat();

	// �������ֲ���
	void _createLayout();

protected:
	String	m_sText;
	bool	m_bWrappingEnable;
	float	m_fWrappingWidth;
	TextStyle	m_TextStyle;
	float	m_fLineSpacing;
	int		m_nAlign;
	IDWriteTextFormat * m_pDWriteTextFormat;
	IDWriteTextLayout * m_pDWriteTextLayout;
};


class Button :
	public Node
{
public:
	// ����һ���հ�ť
	Button();

	// ������ť
	Button(
		Node * normal,			/* ��ͨ״̬ */
		Function func = nullptr	/* ��ť������ִ�к��� */
	);

	// ������ť
	Button(
		Node * normal,			/* ��ͨ״̬ */
		Node * selected,		/* ��갴��״̬ */
		Function func = nullptr	/* ��ť������ִ�к��� */
	);

	// ������ť
	Button(
		Node * normal,			/* ��ͨ״̬ */
		Node * mouseover,		/* �������״̬ */
		Node * selected,		/* ��갴��״̬ */
		Function func = nullptr	/* ��ť������ִ�к��� */
	);

	// ������ť
	Button(
		Node * normal,			/* ��ͨ״̬ */
		Node * mouseover,		/* �������״̬ */
		Node * selected,		/* �������״̬ */
		Node * disabled,		/* ��ť����״̬ */
		Function func = nullptr	/* ��ť������ִ�к��� */
	);

	// ��ȡ��ť״̬�����û��ǽ���
	bool isEnable() const;

	// ���ð�ť���û����
	void setEnable(
		bool bEnable
	);

	// ����һ���������ʾ�İ�ť
	virtual void setNormal(
		Node * normal
	);

	// ����������밴ťʱ��ʾ�İ�ť
	virtual void setMouseOver(
		Node * mouseover
	);

	// ������갴�°�ťʱ��ʾ�İ�ť
	virtual void setSelected(
		Node * selected
	);

	// ���ð�ť������ʱ��ʾ�İ�ť
	virtual void setDisabled(
		Node * disabled
	);

	// ���ð�ť������ִ�к���
	void setClickFunc(
		Function func
	);

	// ���°�ť״̬
	virtual void onFixedUpdate() override;

protected:
	// ��ť״̬ö��
	enum BTN_STATE { NORMAL, MOUSEOVER, SELECTED };

	// ���ð�ť״̬
	virtual void _setState(BTN_STATE state);

	// ˢ�°�ť��ʾ
	virtual void _updateVisiable();

	// ִ�а�ť��������
	virtual void _runCallback();

protected:
	Node *		m_pNormal;
	Node *		m_pMouseover;
	Node *		m_pSelected;
	Node *		m_pDisabled;
	bool		m_bEnable;
	bool		m_bIsSelected;
	BTN_STATE	m_eBtnState;
	Function	m_Callback;
};


class ButtonToggle :
	public Button
{
public:
	// ����һ���յĿ��ذ�ť
	ButtonToggle();

	// �������ذ�ť
	ButtonToggle(
		Node * onNormal,		/* ��ť��ʱ����ͨ״̬ */
		Node * offNormal,		/* ��ť�ر�ʱ����ͨ״̬ */
		Function func = nullptr	/* ��ť������ִ�к��� */
	);

	// �������ذ�ť
	ButtonToggle(
		Node * onNormal,		/* ��ť��ʱ����ͨ״̬ */
		Node * offNormal,		/* ��ť�ر�ʱ����ͨ״̬ */
		Node * onSelected,		/* ��ť��ʱ����갴��״̬ */
		Node * offSelected,		/* ��ť�ر�ʱ����갴��״̬ */
		Function func = nullptr	/* ��ť������ִ�к��� */
	);

	// �������ذ�ť
	ButtonToggle(
		Node * onNormal,		/* ��ť��ʱ����ͨ״̬ */
		Node * offNormal,		/* ��ť�ر�ʱ����ͨ״̬ */
		Node * onMouseOver,		/* ��ť��ʱ���������״̬ */
		Node * offMouseOver,	/* ��ť�ر�ʱ���������״̬ */
		Node * onSelected,		/* ��ť��ʱ����갴��״̬ */
		Node * offSelected,		/* ��ť�ر�ʱ����갴��״̬ */
		Function func = nullptr	/* ��ť������ִ�к��� */
	);

	// �������ذ�ť
	ButtonToggle(
		Node * onNormal,		/* ��ť��ʱ����ͨ״̬ */
		Node * offNormal,		/* ��ť�ر�ʱ����ͨ״̬ */
		Node * onMouseOver,		/* ��ť��ʱ���������״̬ */
		Node * offMouseOver,	/* ��ť�ر�ʱ���������״̬ */
		Node * onSelected,		/* ��ť��ʱ����갴��״̬ */
		Node * offSelected,		/* ��ť�ر�ʱ����갴��״̬ */
		Node * onDisabled,		/* ��ť��ʱ������״̬ */
		Node * offDisabled,		/* ��ť�ر�ʱ������״̬ */
		Function func = nullptr	/* ��ť������ִ�к��� */
	);

	// ��ȡ����״̬���򿪻�رգ�
	bool getState() const;

	// ���ÿ��ذ�ť��״̬���򿪻�رգ�
	void setState(
		bool bState
	);

	// ���ð�ť��״̬����ʾ�İ�ť
	virtual void setNormal(
		Node * normal
	) override;

	// ���ð�ť��״̬�£�������밴ťʱ��ʾ�İ�ť
	virtual void setMouseOver(
		Node * mouseover
	) override;

	// ���ð�ť��״̬�£���갴�°�ťʱ��ʾ�İ�ť
	virtual void setSelected(
		Node * selected
	) override;

	// ���ð�ť��״̬�£�������ʱ��ʾ�İ�ť
	virtual void setDisabled(
		Node * disabled
	) override;

	// ���ð�ť�ر�״̬����ʾ�İ�ť
	void setNormalOff(
		Node * normal
	);

	// ���ð�ť�ر�״̬�£�������밴ťʱ��ʾ�İ�ť
	void setMouseOverOff(
		Node * mouseover
	);

	// ���ð�ť�ر�״̬�£���갴�°�ťʱ��ʾ�İ�ť
	void setSelectedOff(
		Node * selected
	);

	// ���ð�ť�ر�״̬�£���ť������ʱ��ʾ�İ�ť
	void setDisabledOff(
		Node * disabled
	);

protected:
	// ˢ�°�ť����
	virtual void _updateState();

	// ִ�а�ť��������
	virtual void _runCallback() override;

protected:
	Node *	m_pNormalOn;
	Node *	m_pNormalOff;
	Node *	m_pMouseoverOn;
	Node *	m_pMouseoverOff;
	Node *	m_pSelectedOn;
	Node *	m_pSelectedOff;
	Node *	m_pDisabledOn;
	Node *	m_pDisabledOff;
	bool	m_bState;
};


class Menu :
	public Node
{
public:
	// �����ղ˵�
	Menu();

#if HIGHER_THAN_VS2012
	// �����˵�
	Menu(
		const InitList<Button*>& vButtons	/* ��ť���� */
	);
#else
	// �����˵�
	Menu(
		int number,			/* �˵��а�ť������ */
		Button * button1,	/* ��һ����ť */
		...
	);
#endif

	// ��ȡ�˵��Ƿ����
	bool isEnable() const;

	// ��ȡ�˵��еİ�ť����
	size_t getButtonCount() const;

	// ���ò˵����û����
	void setEnable(
		bool enable
	);

	// ���Ӱ�ť
	void addButton(
		Button * button
	);

	// �Ƴ���ť
	bool removeButton(
		Button * button
	);

protected:
	bool m_bEnable;
	std::vector<Button*> m_vButtons;
};

}