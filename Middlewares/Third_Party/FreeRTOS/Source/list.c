  


#include <stdlib.h>
#include "FreeRTOS.h"
#include "list.h"

  

void vListInitialise( List_t * const pxList )
{
	  
	pxList->pxIndex = ( ListItem_t * ) &( pxList->xListEnd );			  

	  
	pxList->xListEnd.xItemValue = portMAX_DELAY;

	  
	pxList->xListEnd.pxNext = ( ListItem_t * ) &( pxList->xListEnd );	  
	pxList->xListEnd.pxPrevious = ( ListItem_t * ) &( pxList->xListEnd );  

	pxList->uxNumberOfItems = ( UBaseType_t ) 0U;

	  
	listSET_LIST_INTEGRITY_CHECK_1_VALUE( pxList );
	listSET_LIST_INTEGRITY_CHECK_2_VALUE( pxList );
}
  

void vListInitialiseItem( ListItem_t * const pxItem )
{
	  
	pxItem->pxContainer = NULL;

	  
	listSET_FIRST_LIST_ITEM_INTEGRITY_CHECK_VALUE( pxItem );
	listSET_SECOND_LIST_ITEM_INTEGRITY_CHECK_VALUE( pxItem );
}
  

void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem )
{
ListItem_t * const pxIndex = pxList->pxIndex;

	  
	listTEST_LIST_INTEGRITY( pxList );
	listTEST_LIST_ITEM_INTEGRITY( pxNewListItem );

	  
	pxNewListItem->pxNext = pxIndex;
	pxNewListItem->pxPrevious = pxIndex->pxPrevious;

	  
	mtCOVERAGE_TEST_DELAY();

	pxIndex->pxPrevious->pxNext = pxNewListItem;
	pxIndex->pxPrevious = pxNewListItem;

	  
	pxNewListItem->pxContainer = pxList;

	( pxList->uxNumberOfItems )++;
}
  

void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem )
{
ListItem_t *pxIterator;
const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;

	  
	listTEST_LIST_INTEGRITY( pxList );
	listTEST_LIST_ITEM_INTEGRITY( pxNewListItem );

	  
	if( xValueOfInsertion == portMAX_DELAY )
	{
		pxIterator = pxList->xListEnd.pxPrevious;
	}
	else
	{
		  

		for( pxIterator = ( ListItem_t * ) &( pxList->xListEnd ); pxIterator->pxNext->xItemValue <= xValueOfInsertion; pxIterator = pxIterator->pxNext )     
		{
			  
		}
	}

	pxNewListItem->pxNext = pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious = pxNewListItem;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext = pxNewListItem;

	  
	pxNewListItem->pxContainer = pxList;

	( pxList->uxNumberOfItems )++;
}
  

UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove )
{
  
List_t * const pxList = pxItemToRemove->pxContainer;

	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

	  
	mtCOVERAGE_TEST_DELAY();

	  
	if( pxList->pxIndex == pxItemToRemove )
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}

	pxItemToRemove->pxContainer = NULL;
	( pxList->uxNumberOfItems )--;

	return pxList->uxNumberOfItems;
}
  

