<h1>Это моя личная реализация стандартного вектора
В main блоке тесты</h1>
<h2>📦 SimpleVector — поддерживаемый интерфейс и сложность</h2>

<h3>Конструкторы</h3>
<table>
  <thead>
    <tr>
      <th>Метод</th>
      <th>Назначение</th>
      <th>Сложность</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>SimpleVector()</td>
      <td>Пустой вектор</td>
      <td>O(1)</td>
    </tr>
    <tr>
      <td>SimpleVector(size_t size)</td>
      <td>Вектор из <code>size</code> элементов (<code>Type{}</code>)</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td>SimpleVector(size_t size, const Type&amp; value)</td>
      <td>Заполнение значением</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td>SimpleVector(std::initializer_list&lt;Type&gt;)</td>
      <td>Инициализация списком</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td>SimpleVector(const SimpleVector&amp;)</td>
      <td>Копирующий конструктор</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td>SimpleVector(SimpleVector&amp;&amp;)</td>
      <td>Перемещающий конструктор</td>
      <td>O(1)</td>
    </tr>
    <tr>
      <td>SimpleVector(ReserveProxyObj)</td>
      <td>Резервирование ёмкости</td>
      <td>O(n)</td>
    </tr>
  </tbody>
</table>

<h3>Операторы присваивания</h3>
<table>
  <thead>
    <tr>
      <th>Метод</th>
      <th>Назначение</th>
      <th>Сложность</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>operator=(const SimpleVector&amp;)</td>
      <td>Копирующее присваивание (copy-swap)</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td>operator=(SimpleVector&amp;&amp;)</td>
      <td>Перемещающее присваивание</td>
      <td>O(1)</td>
    </tr>
  </tbody>
</table>

<h3>Модификаторы</h3>
<table>
  <thead>
    <tr>
      <th>Метод</th>
      <th>Назначение</th>
      <th>Сложность</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>PushBack(const Type&amp;)</td>
      <td>Добавление в конец</td>
      <td>O(1) амортизированная, O(n) при перевыделении</td>
    </tr>
    <tr>
      <td>PushBack(Type&amp;&amp;)</td>
      <td>Добавление (move)</td>
      <td>O(1) амортизированная</td>
    </tr>
    <tr>
      <td>PopBack()</td>
      <td>Удаление последнего элемента</td>
      <td>O(1)</td>
    </tr>
    <tr>
      <td>Insert(pos, value)</td>
      <td>Вставка по позиции</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td>Erase(pos)</td>
      <td>Удаление элемента по позиции</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td>Clear()</td>
      <td>Очистка вектора</td>
      <td>O(1)</td>
    </tr>
    <tr>
      <td>Resize(new_size)</td>
      <td>Изменение размера</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td>Reserve(new_capacity)</td>
      <td>Резервирование памяти</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td>swap(other)</td>
      <td>Обмен содержимым</td>
      <td>O(1)</td>
    </tr>
  </tbody>
</table>

<h3>Доступ к элементам</h3>
<table>
  <thead>
    <tr>
      <th>Метод</th>
      <th>Назначение</th>
      <th>Сложность</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>operator[]</td>
      <td>Доступ без проверки</td>
      <td>O(1)</td>
    </tr>
    <tr>
      <td>At(index)</td>
      <td>Доступ с проверкой границ</td>
      <td>O(1)</td>
    </tr>
  </tbody>
</table>

<h3>Итераторы</h3>
<table>
  <thead>
    <tr>
      <th>Метод</th>
      <th>Назначение</th>
      <th>Сложность</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>begin() / end()</td>
      <td>Итераторы</td>
      <td>O(1)</td>
    </tr>
    <tr>
      <td>cbegin() / cend()</td>
      <td>Константные итераторы</td>
      <td>O(1)</td>
    </tr>
  </tbody>
</table>

<h3>Информация о контейнере</h3>
<table>
  <thead>
    <tr>
      <th>Метод</th>
      <th>Назначение</th>
      <th>Сложность</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>GetSize()</td>
      <td>Количество элементов</td>
      <td>O(1)</td>
    </tr>
    <tr>
      <td>GetCapacity()</td>
      <td>Ёмкость</td>
      <td>O(1)</td>
    </tr>
    <tr>
      <td>IsEmpty()</td>
      <td>Проверка на пустоту</td>
      <td>O(1)</td>
    </tr>
  </tbody>
</table>

<h3>Операторы сравнения</h3>
<table>
  <thead>
    <tr>
      <th>Оператор</th>
      <th>Сложность</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>==, !=</td>
      <td>O(n)</td>
    </tr>
    <tr>
      <td>&lt;, &lt;=, &gt;, &gt;=</td>
      <td>O(n)</td>
    </tr>
  </tbody>
</table>
