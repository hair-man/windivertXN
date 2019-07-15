#ifndef __RING_BUFFER__
#define __RING_BUFFER__

/** @file
*  ���ļ��а����˻��ζ��п�������ⲿ�ӿںꡣ
*
*  ���ζ��п�������ⲿ�ӿڶ����Ժ����ʽ���ֵġ�ʵ�����������ζ��п���ɱ�ͷ�ļ����ɡ�
*  <p>һ�����ζ����߼�������һ�����顢һ����ָ���һ��дָ�빹�ɵġ�
*  <p>��ָ��ָʾ������һ�ν�����ȡ��Ԫ�ص��±꣬дָ��ָʾ������һ�α�д����е�Ԫ�ص��±ꡣ
*  <p>����ָ�����дָ��ʱ����ʾ����Ϊ�ա���дָ�뽫ָ�����һ��Ϊλ��Ϊ��ָ��ָʾλ��ʱ����ʾ����Ϊ����
*  <p>ÿ���������д��һ��Ԫ��ʱ��ֱ�ӽ�д���Ԫ�ر����õ�дָ������λ�ã�Ȼ��дָ�뽫��ǰ�ƶ�һ��λ�á�
*  <p>ÿ�δӶ��ж�ȡһ��Ԫ��ʱ����ֱ��ȡ��ָ����ָλ�õ�Ԫ�أ�Ȼ���ָ�뽫��ǰ�ƶ�һ��λ�á�
*
*  <p>�ڱ���ʵ�ֻ��ζ��е�ʱ�򣬳��˻��ζ��еĻ�������֮�⣬�����ǵ�������2������������
*  <ol>
*	<li>�����ڻ��ζ����е�Ԫ��Ӧ�ÿ������κ����͡����ڻ��ζ�����˵����������֮������������Ϊ��ռ�ռ�Ĵ�С��ͬ����һ�����������ɵĻ��ζ��к�һ���ɶ��������ɵĻ��ζ��д��߼���˵��ִ�еĲ�������ͬ��ֻ����ʵ��ʱ��Ҫ���ǵ��������͵Ĳ�ͬ��</li>
*  <li>Ϊ�˽����ζ���������Ӧ�÷���ļ�����������������Ҫ�ɻ��ζ����Լ��������ڴ档</li>
*  </ol>
*
*  <p>�ڱ���ʵ���У����ζ������ڴ��еĽṹ����ͼ��ʾ��
*  <pre>
*����������������������
*��       rsize      ��
*����������������������
*��       bsize      ��
*����������������������
*��        wp        ��
*����������������������
*��        rp        ��
*����������������������
*��  ���ζ��е�Ԫ��  ��
*��    ..........    ��
*��                  ��
*��                  ��
*��                  ��
*��                  ��
*��                  ��
*��                  ��
*����������������������
* </pre>
*/

#include <stdint.h>
#include <malloc.h>

/** �����ζ��еĽṹ��
*  �û�ʹ�û��ζ��п�ʱ������Ҫֱ��ʹ�øýṹ��
*/
typedef struct __ring_buffer
{
	int rsize;	/**< ���滷�ζ�����Ԫ�صĸ�������һ�����ζ������ܹ�����Ԫ�ص����������rsize-1��*/
	int bsize;	/**< ���滷�ζ�����ÿ��Ԫ����ռ�ռ�Ĵ�С��*/
	volatile int wp;	/**< wp��дָ�롣 */
	volatile int rp;	/**< rp�Ƕ�ָ�롣 */
}RING_BUFFER;

/** PRING_BUFFER������ΪRING_BUFFER*	*/
typedef RING_BUFFER* PRING_BUFFER;

/** @def rb_memory_required(rs, bs)
*  ����һ������\a rs ��\a bs ��С��Ԫ�صĻ��ζ�������Ҫռ�õ��ڴ��С��
*  �ú��ֵ���������ڴ��С��
*/
#define rb_memory_required(rs, bs) (sizeof(RING_BUFFER) + (bs) * ((rs)+1))

/** @def rb_initialize(rs, bs, pbuf)
*  ��\a pbuf ��ָ����ڴ��У���ʼ��һ������\a rs ��\a bs ��С��Ԫ�صĻ��ζ��С����л��ζ�����ʹ��֮ǰ������������\a rb_initialize ���г�ʼ����
*  �ú��ֵΪ0ʱ��ʾ��ʼ�����ɹ��������ʾ��ʼ���ɹ����ɹ���ʼ��֮��rp��wp��Ϊ0����ʾ����Ϊ�ա�
*/
#define rb_initialize(rs, bs, pbuf)	\
	((pbuf)==0 ? 0 : (((PRING_BUFFER)(pbuf))->bsize = (bs), ((PRING_BUFFER)(pbuf))->rsize = (rs)+1, ((PRING_BUFFER)(pbuf))->rp = ((PRING_BUFFER)(pbuf))->wp = 0, (pbuf)))

/** @def rb_create(rs, bs, pbuf)
*  ����\a rs �� \a bs ����һ�����ζ��У�\a pbuf ָ������֮��Ļ��ζ��С�
*  �ú��ֵΪ0ʱ��ʾ���ɲ��ɹ��������ʾ���ɳɹ���
*/
#define rb_create(rs, bs, pbuf) (pbuf=malloc(rb_memory_required(rs, bs)), rb_initialize(rs, bs, pbuf))

/** @def rb_incPtr(prb, ptr)
*  ��\a prb ��ֵ���1�������1֮��\a prb ��ֵ��С��\a rsize ��\a prb ��Ϊ0��\a ptr ָ��һ���ɹ���ʼ���Ļ��ζ��С�
*  �ú��ֵΪ��1֮��prb��ֵ��
*/
#define rb_incPtr(prb, ptr) ((ptr)=(((ptr)+1)%(((PRING_BUFFER)(prb))->rsize)))

/** @def rb_canRead(prb)
*  �ж��Ƿ�ɴ�\a prb ��ָ��Ļ��ζ����ж���Ԫ�ء�
*  �ú��ֵΪ0ʱ����ʾ���ɶ��������ʾ�ɶ���
*/
#define rb_canRead(prb) (((PRING_BUFFER)(prb))->wp != ((PRING_BUFFER)(prb))->rp)

/** @def rb_canWrite(prb)
*  �ж��Ƿ������\a prb ��ָ��Ļ��ζ�����д��Ԫ�ء�
*  �ú��ֵΪ0ʱ����ʾ����д�������ʾ����д��
*/
#define rb_canWrite(prb) (((((PRING_BUFFER)(prb))->wp + 1) % (((PRING_BUFFER)(prb))->rsize)) != ((PRING_BUFFER)(prb))->rp)

/** @def rb_dataBuffer(prb, T)
*  ���ػ��ζ����ж���Ԫ��������׵�ַ��\a prb ָ���ζ��У�\a T ΪԪ�ص����͡�
*/
#define rb_dataBuffer(prb, T) ((T*)(((unsigned char*)(prb))+sizeof(RING_BUFFER)))

/** @def rb_writePeek(prb, T)
*  ȡ�ؽ�д��Ԫ�ء�\a prb ָ���ζ��У�\a T ΪԪ�ص����͡�
*/
#define rb_writePeek(prb, T) (rb_dataBuffer(prb, T)[((PRING_BUFFER)(prb))->wp])

/** @def rb_readPeek(prb, T)
*  ȡ�ؽ�����Ԫ�ء�\a prb ָ���ζ��У�\a T ΪԪ�ص����͡�
*/
#define rb_readPeek(prb, T) (rb_dataBuffer(prb, T)[((PRING_BUFFER)(prb))->rp])

/** @def rb_writeIn(prb)
*  ��ǰ�ƶ�дָ�룬���д������\a prb ָ���ζ��С�
*/
#define rb_writeIn(prb) rb_incPtr((prb), ((PRING_BUFFER)(prb))->wp)

/** @def rb_readOut(prb)
*  ��ǰ�ƶ���ָ�룬��ɶ�������\a prb ָ���ζ��С�
*/
#define rb_readOut(prb) rb_incPtr((prb), ((PRING_BUFFER)(prb))->rp) 

/** @def rb_writeInValue(prb, T, V)
*  ��\a prb ��ָ��Ļ��ζ�����д��һ������Ϊ\a T ��ֵΪ\a V ��Ԫ�ء�
*/
#define rb_writeInValue(prb, T, V) (rb_canWrite(prb) ? ((rb_writePeek(prb, T))=(V), rb_writeIn(prb), 1): 0)

/** @def rb_readOutValue(prb, T, V)
*  ��\a prb ��ָ��Ļ��ζ����ж�ȡһ������Ϊ\a T ��ֵΪ\a V ��Ԫ�ء�
*/
#define rb_readOutValue(prb, T, V) (rb_canRead(prb)  ? ((V)=(rb_readPeek(prb,T)), rb_readOut(prb), 1): 0)

#define rb_occupied_slots(prb) ((((PRING_BUFFER)(prb))->wp - ((PRING_BUFFER)(prb))->rp+((PRING_BUFFER)(prb))->rsize) % (((PRING_BUFFER)(prb))->rsize))
#define rb_empty_slots(prb) (((PRING_BUFFER)(prb))->rsize - rb_occupied_slots(prb) - 1)
#endif


