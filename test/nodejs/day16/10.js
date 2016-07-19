/**
 * Created by KICT-04 on 2016-07-19.
 */

let array_test = ['banana','orange','apple','mango','raspberry'];
array_test.splice(
    2, //삽입 위치
    2, //삭제 원소 갯수
    "grape","peanut");  //삽입 내용
console.log(array_test);

array_test.splice(2,1);

console.log(array_test);