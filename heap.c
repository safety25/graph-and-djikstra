/*
 * tp05.c
 *
 *  Created on: 15 Kas 2022
 *      Author: pinar
 */

#include <stdio.h>
#include <limits.h>
#include <assert.h>

/* swap islemi icin macro, ayrica fonksiyon yazmaniza gerek yok */
static int _temp;
#define SWAP(a,b) do { \
  _temp = a; \
  a = b; \
  b = _temp; \
} while (0)

/* heap'i temsil eden dizinin uzunlugu */
static int SIZE = 10;

/* heap taklidi yapan dizinin elemanlarini ekrana bastiran fonksiyon
 * array: heap, size: heap'teki mevcut eleman sayisi */
void print_heap(int *arr, int size);

/* algoritmasi TP dosyasinda verilmis olan ve heap ozelligi bozulmus bir diziyi heap haline getiren fonksiyon, yonu: kokten yapraga
 * array: heap, index: heap ozelligini bozan elemanin asagi iteklenecek indeksi, size: heap'teki mevcut eleman sayisi */
void max_heapify_recursive(int *arr, int index, int size);

/* parametre olarak aldigi bir diziden max-heap ozelligini koruyan binary heap olusturan rekursif fonksiyon
 * array: heap, size: heap'teki mevcut eleman sayisi */
void build_max_heap(int *arr, int size);

/* oncelikli kuyruktaki maksimum oncelikli elemani donduren ve de elemani kuyruktan cikarip heap ozelliginin korunmasini da saglayan fonksiyon
 * arr: heap, size: heap'teki mevcut eleman sayisi */
int extractMax(int *arr, int size);

/* heap ozelligi bozulmus bir diziyi heap haline getiren fonksiyon, yonu: yapraktan koke
 * arr: heap, index: heap ozelligini bozan elemanin yukari iteklenecek indeksi */
void bubbleUp(int *arr, int index);

/* oncelikli kuyruga eleman ekleyen ve heap ozelligini korumasini saglayan fonksiyon
 * arr: heap, data: eklenecek elemanin degeri (ya da onceligi, bizim durumumuzda ikisi de ayni) */
void insertData(int *arr, int data);

/* oncelikli kuyruktan verilen indeksteki elemani cikaran ve heap ozelligini korumasini saglayan fonksiyon
 * arr: heap, index: cikarilacak elemanin indeksi */
void removeIndex(int *arr, int index);

/* oncelikli kuyrukta indeksi verilen elemanin degerini (onceligini) degistiren fonksiyon
 * arr: heap, index: onceligi guncellenecek elemanin indeksi, priority: yeni oncelik degeri */
void changePriority(int *arr, int index, int priority);

int main() {

	int arr1[] = { 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
	int arr2[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	int heap[] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };

	printf("\n<<<Program baslangici>>>\n");

	// max_heapify_recursive fonksiyonunu arr1'in max-heap ozelligini bozan elemani icin cagirin
	printf(">> arr1 icin max_heapify_recursive cagrildi! \n");
	max_heapify_recursive(arr1, 1, SIZE);

	// guncellenmis heap'i ekrana bastirin
	printf("heap: ");
	print_heap(arr1, SIZE);

	int i;
	// max_heapify_recursive icin test durumu
	for (i = 0; i < SIZE; i++)
		assert(arr1[i] == heap[i]);
	printf("\n>> max_heapify_recursive sorunsuz calisiyor, yola devam...\n");

	// build_max_heap ile arr2'yi heap haline getirin
	printf(">>arr2 icin build_max_heap cagrildi\n");
	build_max_heap(arr2, SIZE);

	// heap'i ekrana bastirin
	printf("heap: ");
	print_heap(arr2, SIZE);

	// build_max_heap icin test durumu
	for (i = 0; i < SIZE; i++)
		assert(arr2[i] == heap[i]);
	printf("\n>> build_max_heap sorunsuz calisiyor, yola devam...\n");

	// bundan sonraki islemleri heap dizisi uzerinde oncelikli kuyruk fonksiyonlarini kullanarak yerine getirecegiz
	printf("\n----- Oncelikli kuyruk -----\n");
	// oncelikli kuyruktaki en yuksek oncelikli elemani kuyruktan cekin, guncellenmis kuyruk yapisini ve cektiginiz eleman degerini ekrana bastirin

	printf("\n>> extracted max : %d\n", extractMax(heap, SIZE));
	printf("kuyruk: ");
	print_heap(heap, SIZE);

	// bir onceki islemi tekrarlayin
	printf("\n>> extracted max : %d", extractMax(heap, SIZE));
	printf("\nkuyruk: ");
	print_heap(heap, SIZE);

	// oncelikli kuyruga degeri (onceligi) 35 olan bir eleman ekleyin ve kuyrugu ekrana bastirin
	insertData(heap, 35);
	printf("\n>> 35 eklendi");
	printf("\nkuyruk : ");
	print_heap(heap, SIZE);

	// oncelikli kuyruktan 5 indeksli elemani cikarin ve kuyrugu ekrana bastirin
	removeIndex(heap, 5);
	printf("\n>> indexi 5 olan eleman kuyruktan cikarildi");
	printf("\nkuyruk : ");
	print_heap(heap, SIZE);


	// oncelikli kuyrugun 3 indeksli elemaninin onceligini 41 yapin ve kuyrugu ekrana bastirin
	changePriority(heap, 3, 41);
	printf("\n>> onceligi 8 olan elemanin onceligi guncellendi");
	printf("\nkuyruk : ");
	print_heap(heap, SIZE);

	return 0;
}

void print_heap(int *arr, int size) {
	if (arr == NULL)
	{
		printf("Array is empty!");
	}
	else {
		for (int i = 0; i < size; i++){
			printf("%d  ", arr[i]);
		}
	}
	
}

void max_heapify_recursive(int *arr, int index, int size) {
	if (size == 1)
  {
    printf("Single element in the heap");
  }
  else
  {
	// en buyuk elemanin indeksini index kabul et (parent)
    int largest = index;
	// index'in sol cocugunun dizi indeksini hesapla
    int l = 2 * index + 1;
	// index'in sag cocugunun dizi indeksini hesapla
    int r = 2 * index + 2;
	
	// sol cocuk parent'tan buyukse kaydet
    if (l < size && arr[l] > arr[largest]){
		largest = l;
	}
      
	// sag cocuk kayitli buyukten buyukse kaydet
    if (r < size && arr[r] > arr[largest]){
		largest = r;
	}

	// Cocuklardan biri buyuk olarak kaydedildiyse parent ile onu degistirip, yeni buyuk icin rekursif cagri yap
    if (largest != index)
    {
      SWAP(arr[index], arr[largest]);
      max_heapify_recursive(arr, largest, size);
    }
  }
	
}

void build_max_heap(int *arr, int size) {
	// ders notlarindaki algoritma (slide no: 110)
	int max_heap = size/2-1;
	for(int i = max_heap; i >= 0; i--){
		max_heapify_recursive(arr, i, size);
	}
}

int extractMax(int *arr, int size) {
	// kok degerini yedekle

	int root = arr[0];

	// kokun degerini, en son siradaki en sagdaki yaprak degeri ile degistir ve eleman sayisini guncelle
	SWAP(arr[0], arr[size-1]);
	SIZE = SIZE - 1;


	// heap ozelligini korumak icin heapify ile yeni koku agacta olmasi gereken yere gonder
	for(int i = SIZE/2; i>=0; i--){
		max_heapify_recursive(arr, i, SIZE);
	}
	
	// kok degerini gonder
	return root;
}

void bubbleUp(int *arr, int index) {
	// ders notlarindaki algoritma (slide no: 97)
	while(index > 0 && (arr[index/2-1] < arr[index] || arr[index/2-1] < arr[index])){
		if(index%2 == 0){
			SWAP(arr[index], arr[index/2-1]);
			index = index/2-1;
		}
		else if(index%2 == 1){
			SWAP(arr[index], arr[index/2]);
			index = index/2;
		}
	}
}

void insertData(int *arr, int data) {
	// heap'in uzunlugunu artir
	SIZE += 1;
	
	// en son indekse yeni eleman degerini ekle
	arr[SIZE-1] = data;
	
	// heap ozelligini korumak icin bubbleUp'i cagir
	bubbleUp(arr, SIZE-1);
}

void removeIndex(int *arr, int index) {
	// cikarilacak index'teki eleman degerine sonsuz veremiyoruz, INT_MAX veriyoruz
	arr[index] = INT_MAX;

	// bu yuksek degerli elemani koke dogru itekle
	bubbleUp(arr, index);

	// kokten cikar
	extractMax(arr, SIZE);
}

void changePriority(int *arr, int index, int priority) {
	// onceki priority'si yenisinden buyukse koke dogru , degilse yapraklara dogru itekle
	int prev = arr[index];
	arr[index] = priority;
	// onceki priority'si yenisinden buyukse koke dogru , degilse yapraklara dogru itekle
	if(prev < priority){
		bubbleUp(arr, index);
	}
	else{
		for (int i = SIZE/2; i >= 0; i--)
		{
			max_heapify_recursive(arr, index, SIZE);
		}
		
		
	}
}