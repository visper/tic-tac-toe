#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#define M_WIDTH 3

struct matrix{
  int **matrix;
};

//все прототипы функций
int matrix_init(struct matrix **m);
//int check_place(struct matrix **m, const size_t count_steps);
int rand_generator(void); // maybe inline
void get_computer_move(struct matrix **m, const size_t count_steps);
void get_player_move(struct matrix **m);
int check_winner(struct matrix **m, const size_t count_steps);
void matrix_fini(struct matrix **m);
void matrix_print(const struct matrix *m);




int matrix_init(struct matrix **m)
{
  *m = (struct matrix*)malloc(sizeof(struct matrix));
  if(m == 0)
    return -ENOMEM;

  (*m) -> matrix = (int**)malloc(M_WIDTH * sizeof(int*));
  if((*m) -> matrix == 0)
    return -ENOMEM;

  //элементы находятся рядом
  //int **m = (int **) malloc(sizeof(int *) * SIZE);
  //int (*m)[nSize] = (int(*)[nSize])malloc(nSize * sizeof(int[nSize]));
  for(size_t i = 0; i < M_WIDTH; ++i){
    (*m) -> matrix[i] = (int*)malloc(M_WIDTH * sizeof(int));

    if((*m) -> matrix[i] == 0)
      return -ENOMEM;
  }

    //заполнение матрицы
  //  (*m) -> matrix[1][1] = 1;
  for(size_t i = 0; i < M_WIDTH; ++i){
    for(size_t j = 0; j < M_WIDTH; ++j){
      (*m) -> matrix[i][j] = 0;
    }
  }
  return 0;
}

/*
//проверка свободных ходов
//return 1 если нет свободного места
//return 0 если место есть
int check_place(struct matrix **m, const size_t count_steps)
{
  size_t busy = 0;//занятые ячейки
  for(size_t i = 0; i < M_WIDTH; ++i){
    for(size_t j = 0; j < M_WIDTH; ++j){
      if((*m) -> matrix[i][j])
	++busy;
    }
  }

  if(busy < (M_WIDTH * M_WIDTH))
    return 0;
  else 
    return 1;
}
*/

//простматривает матрицу для поиска свободных ячеек
void get_computer_move(struct matrix **m, const size_t count_steps)
{
  size_t done = 1;
  while( done ){
    size_t a = 0 + rand() % M_WIDTH;
    size_t b = 0 + rand() % M_WIDTH;
    if(((*m) -> matrix[a][b]) == 0 ){
      (*m) -> matrix[a][b] = 2;
      done = 0;
    }
      //map можно удалить и сравнивать сразу с (*m)
  }
}


//спрашивает где игрок хочет поместить символ
//@return 0 if nobody win
void get_player_move(struct matrix **m)
{
  size_t i = 0, j = 0;
  size_t done = 1;

  while(done){
    printf("enter position: row, column\n");
    //    printf("enter position x, y\n");
    scanf("%zu %zu", &i, &j);
    //check hight input
    if(i >= 0 && i < 3 && j >= 0 && j < 3){
      if( !((*m) -> matrix[i][j]) ){
	(*m) -> matrix[i][j] = 1;
	done = 0;
      }
      else{
	printf("wrong place\n");
      }
    }
    else{
      i = 0;
      j = 0;
      printf("wrong place\n");
      continue;
    }//else
  }//while
}

/*
//проверяет есть ли победитель
int check_winner(struct matrix **m, const size_t count_steps)
{
  //нужно отследить количество ходов
  //по которому определить смотреть или нет 
  //возможные комбинации

  //игрок ходит первый, т.е. на 4 ход может
  //произойти победа
  if(count_steps > 4){
    //могут быть выигришы 
       //по вертикали - 3
       //по горизонтали - 3
       //по диагонали - 2

    //по вертикали

    size_t column = 0, row = 0, diag = 0;
    size_t column_prev = 0, row_prev = 0, diag_prev = 0;

    //ROW!!!
    for(size_t i = 0; i < M_WIDTH; ++i){
      for(size_t j = 0; j < M_WIDTH; ++j){
	//column
	if(j == 0){
	  if( (*m) -> matrix[i][j] == 0 ){
	    break;
	  }
	  column_prev = (*m) -> matrix[i][j];
	}
	
	if(column_prev == (*m) -> matrix[i][j]){
	  column++;
	}
	
	if(j != 0){
	  if(column_prev != (*m) -> matrix[i][j])
	    break;
	}
      }
      if(column == 3)
	return column_prev;

      column = 0;
      column_prev = 0;
    }
    //END_ROW!!!


    //переписать проверка чтобы 0 не считался    
    for(size_t i = 0; i < M_WIDTH; ++i){
      for(size_t j = 0; j < M_WIDTH; ++j){
	//row
	if(j == 0){
	  if( (*m) -> matrix[i][j] == 0 ){
	    break;
	  }
	  row_prev = (*m) -> matrix[j][i];
	}

	if(column_prev == (*m) -> matrix[j][i]){
	  row++;
	}

	if(j != 0){
	  if(column_prev != (*m) -> matrix[j][i])
	    break;
	}
      }
      if(row == 3)
	return column_prev;

      row = 0;
      row_prev = 0;
    }
    
    //diag
    for(size_t i = 0; i < M_WIDTH; ++i){
      size_t j = 0;

      if(i == 0){
	if( (*m) -> matrix[i][j] == 0 ){
	  break;
	}
	diag_prev = (*m) -> matrix[i][j];
      }

      if(diag_prev == (*m) -> matrix[i][j]){
	++diag;
      }

      if(i != 0 && diag_prev != (*m) -> matrix[i][j]){
	break;
      }
      j++;
    }
    if(diag == 3) return diag_prev;

    diag = 0;
    diag_prev = 0;

    for(size_t i = 2; i < 0; --i){
      size_t j = 2;

      if(i == 0){
	if( (*m) -> matrix[i][j] == 0 ){
	  break;
	}
	diag_prev = (*m) -> matrix[i][j];
      }

      if(diag_prev == (*m) -> matrix[i][j]){
	++diag;
      }

      if(i != 0 && diag_prev != (*m) -> matrix[i][j]){
	break;
      }
      j--;
    }
    if(diag == 3)
      return diag_prev;
  }
  else return 0;
}
*/

//проверяет есть ли победитель
int check_winner(struct matrix **m, const size_t count_steps)
{
  //проход по дагонали для проверки где вообще есть элементы
  //если по иагонали все 0 то нет победителя
  //если есть где-то не 0 тотуда нужно посмотреть

  if(count_steps > 4){

    size_t column = 0, row = 0, diag = 0;
    size_t column_prev = 0, row_prev = 0, diag_prev = 0;

    size_t arr[M_WIDTH] = {0};
    size_t j = 0;

    //check diagonal with note numbers in arr
    for(size_t i = 0; i < M_WIDTH; ++i){

      if( (*m) -> matrix[i][j] != 0){
	arr[i] = (*m) -> matrix[i][j];
      }

      ++j;
    }

    j = 0;
    //check arr to know where is number not equal 0
    for(size_t i = 0; i < M_WIDTH; ++i){

      if(i == 0){
	diag_prev = *arr;
	++diag;
      }
      
      if(i != 0 && diag_prev == (*m) -> matrix[i][j]){
	++diag;
      }
      
      ++j;
    }
    if(diag == 3)
      return diag_prev;
    else{
      diag = 0;
      diag_prev = 0;
    }

    //теперь диагонать проверена,
    //проходим по массиву, смотрим где есть значение
    //не равное 0 и из той точки пробегаем двойной массив 
    //во все стороны

    if(*arr != 0){
      //диагональ уже проверена
      //пробегаем столбец и строку
      column_prev = row_prev = *arr;
      column++;
      row++;

      size_t j = 0;
      for(size_t i = 1; i < M_WIDTH; ++i){
	if( (*m) -> matrix[j][i] == column_prev){
	    ++column;
	}

	if( (*m) -> matrix[i][j] == row_prev){
	    ++row;
	}
      }//for

      //check numbers of equal values
      if(column == 3){
	return column_prev;
      }
      
      if(row == 3){
	return row_prev;
      }
    }//if(*arr != 0){

    //if in center element is not equal 0,
    //we must check column, row, and invert diagonal
    if(arr[1] != 0){

      //invert diag
      size_t j = 1;
      diag_prev = 0;
      diag = 0;
      diag_prev = (*m) -> matrix[2][0];
      diag++;
      for(size_t i = 1; i < M_WIDTH; ++i){
	if(diag_prev == (*m) -> matrix[j][i]){
	  diag++;
	}
	--j;
      }

      if(diag == 3)
	return diag_prev;

      //column, row
      column = row = row_prev = column_prev = 0;

      column_prev = (*m) -> matrix[0][1];
      column++;

      row_prev = (*m) -> matrix[1][0];
      row++;

      for(size_t i = 1; i < M_WIDTH; ++i){
	if(column_prev == (*m) -> matrix[i][1]){
	  column++;
	}

	if(row_prev == (*m) -> matrix[1][i]){
	  row++;
	}
      }
      if(row == 3)
	return row_prev;
      if(column == 3)
	return column_prev;
    }

    if(arr[2] != 0 ){
      //диагональ уже проверена
      //пробегаем столбец и строку
      column = 0;
      row = 0;
      column_prev = row_prev = arr[2];
      column++;
      row++;

      int j = 2;
      for(int i = 1; i >= 0; --i){
	if( (*m) -> matrix[j][i] == row_prev){
	    ++row;
	}

	if( (*m) -> matrix[i][j] == column_prev){
	    ++column;
	}
      }

      //check numbers of equal values
      if(column == 3)
	return column_prev;
      
      if(row == 3)
	return row_prev;
      
    }//if(*arr+2 != 0 )
    return 0;
  }
  else return 0;
}

//очистка памяти занимаемой структурой
void matrix_fini(struct matrix **m)
{
  for(size_t i = 0; i < M_WIDTH; ++i){
    free((*m) -> matrix[i]);
  }

  free((*m) -> matrix);

  free(*m);
}

//вывод матрицы
void matrix_print(const struct matrix *m)
{
  for(size_t i = 0; i < M_WIDTH; ++i){
    printf("\n");
    for(size_t j = 0; j < M_WIDTH; ++j){
      printf("%i ", m -> matrix[i][j]);
    }
  }
  printf("\n");
}

int main(int argc, char** argv)
{
  /*
    int matrix_init(struct matrix **m);
    int check_place(struct matrix **m, const size_t *count_steps);
    int rand_generator(void); // maybe inline
    void get_computer_move(struct matrix **m, const size_t *count_steps);
    void get_player_move(struct matrix **m);
    int check_winner(struct matrix **m, const size_t *count_steps);
    void matrix_fini(struct matrix **m);
    void matrix_print(const struct matrix *m);
  */

  static size_t count_steps = 0;

  //инициализация матрицы
  struct matrix *m1;
  
  matrix_init(&m1);
  matrix_print(m1);

  //  printf("%i\n", m1 -> matrix[1][1]);

  //  while(! check_place(&m1, count_steps)){
  while(count_steps != 10){

    get_player_move(&m1);
    ++count_steps;
    matrix_print(m1);

    //printf("%i\n", count_steps);

    //if check_winner != 0 go into if
    size_t winner = 0;
    winner = check_winner(&m1, count_steps);

    if(winner){
      assert(winner != 0);
      printf("player %zu, wins, congratulations!\n", winner);
      break;
    }
    /*
    //@return 0 if place is enable
    size_t place = 0;
    place = check_place(&m1, count_steps);

    if(!place){
      assert(place == 0);
      printf("no place to do next step\ngame over!\n");
      break;
    }
    */
    if(count_steps == 9){
      printf("no place to do next step\ngame over!\n");
      matrix_fini(&m1);
      //this can change because programm can work in loop
      return 0;
    }
    if(count_steps != 9){
      get_computer_move(&m1, count_steps);
      ++count_steps;
      matrix_print(m1);

      //printf("%i\n", count_steps);

      //check after player 2
      winner = check_winner(&m1, count_steps);
      
      if(winner){
	assert(winner != 0);
	printf("player %zu, wins, congratulations!\n", winner);
	break;
      }
      /*
	place = check_place(&m1, count_steps);
	if(!place){
	assert(place == 0);
	printf("no place to do next step\ngame over!\n");
	break;
	}
      */
    }
    else{
      printf("no place to do next step\ngame over!\n");
      matrix_fini(&m1);
      //this can change because programm can work in loop
      return 0;
    }
  }

  printf("no place to do next step\ngame over!\n");
  matrix_fini(&m1);

  return 0;

}
