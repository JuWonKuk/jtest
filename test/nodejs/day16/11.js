/**
 * Created by KICT-04 on 2016-07-19.
 */

let array_test = [
    {
        name : 'soek',
        hp : 52
    },
    {
        name : 'mongu',
        hp : 27
    },
    {
        name : 'trol',
        hp : 47
    },
    {
        name : 'orc',
        hp : 35
    },
    {
        name : 'witch',
        hp : 17
    }
];

console.log(array_test);

array_test.sort((left,right)=> {
    //return left.hp - right.hp; 오름차순
    return right.hp - left.hp;
} );
console.log('----------------');
console.log(array_test);