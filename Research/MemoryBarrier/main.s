
main:     file format elf64-x86-64


Disassembly of section .init:

0000000000400468 <_init>:
  400468:	48 83 ec 08          	sub    $0x8,%rsp
  40046c:	48 8b 05 85 0b 20 00 	mov    0x200b85(%rip),%rax        # 600ff8 <_DYNAMIC+0x200>
  400473:	48 85 c0             	test   %rax,%rax
  400476:	74 05                	je     40047d <_init+0x15>
  400478:	e8 23 00 00 00       	callq  4004a0 <__gmon_start__@plt>
  40047d:	48 83 c4 08          	add    $0x8,%rsp
  400481:	c3                   	retq   

Disassembly of section .plt:

0000000000400490 <__gmon_start__@plt-0x10>:
  400490:	ff 35 72 0b 20 00    	pushq  0x200b72(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400496:	ff 25 74 0b 20 00    	jmpq   *0x200b74(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40049c:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004004a0 <__gmon_start__@plt>:
  4004a0:	ff 25 72 0b 20 00    	jmpq   *0x200b72(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  4004a6:	68 00 00 00 00       	pushq  $0x0
  4004ab:	e9 e0 ff ff ff       	jmpq   400490 <_init+0x28>

00000000004004b0 <__libc_start_main@plt>:
  4004b0:	ff 25 6a 0b 20 00    	jmpq   *0x200b6a(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  4004b6:	68 01 00 00 00       	pushq  $0x1
  4004bb:	e9 d0 ff ff ff       	jmpq   400490 <_init+0x28>

Disassembly of section .text:

00000000004004c0 <_start>:
  4004c0:	31 ed                	xor    %ebp,%ebp
  4004c2:	49 89 d1             	mov    %rdx,%r9
  4004c5:	5e                   	pop    %rsi
  4004c6:	48 89 e2             	mov    %rsp,%rdx
  4004c9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4004cd:	50                   	push   %rax
  4004ce:	54                   	push   %rsp
  4004cf:	49 c7 c0 f0 06 40 00 	mov    $0x4006f0,%r8
  4004d6:	48 c7 c1 80 06 40 00 	mov    $0x400680,%rcx
  4004dd:	48 c7 c7 c5 05 40 00 	mov    $0x4005c5,%rdi
  4004e4:	e8 c7 ff ff ff       	callq  4004b0 <__libc_start_main@plt>
  4004e9:	f4                   	hlt    
  4004ea:	66 90                	xchg   %ax,%ax
  4004ec:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004004f0 <deregister_tm_clones>:
  4004f0:	b8 37 10 60 00       	mov    $0x601037,%eax
  4004f5:	55                   	push   %rbp
  4004f6:	48 2d 30 10 60 00    	sub    $0x601030,%rax
  4004fc:	48 83 f8 0e          	cmp    $0xe,%rax
  400500:	48 89 e5             	mov    %rsp,%rbp
  400503:	77 02                	ja     400507 <deregister_tm_clones+0x17>
  400505:	5d                   	pop    %rbp
  400506:	c3                   	retq   
  400507:	b8 00 00 00 00       	mov    $0x0,%eax
  40050c:	48 85 c0             	test   %rax,%rax
  40050f:	74 f4                	je     400505 <deregister_tm_clones+0x15>
  400511:	5d                   	pop    %rbp
  400512:	bf 30 10 60 00       	mov    $0x601030,%edi
  400517:	ff e0                	jmpq   *%rax
  400519:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400520 <register_tm_clones>:
  400520:	b8 30 10 60 00       	mov    $0x601030,%eax
  400525:	55                   	push   %rbp
  400526:	48 2d 30 10 60 00    	sub    $0x601030,%rax
  40052c:	48 c1 f8 03          	sar    $0x3,%rax
  400530:	48 89 e5             	mov    %rsp,%rbp
  400533:	48 89 c2             	mov    %rax,%rdx
  400536:	48 c1 ea 3f          	shr    $0x3f,%rdx
  40053a:	48 01 d0             	add    %rdx,%rax
  40053d:	48 d1 f8             	sar    %rax
  400540:	75 02                	jne    400544 <register_tm_clones+0x24>
  400542:	5d                   	pop    %rbp
  400543:	c3                   	retq   
  400544:	ba 00 00 00 00       	mov    $0x0,%edx
  400549:	48 85 d2             	test   %rdx,%rdx
  40054c:	74 f4                	je     400542 <register_tm_clones+0x22>
  40054e:	5d                   	pop    %rbp
  40054f:	48 89 c6             	mov    %rax,%rsi
  400552:	bf 30 10 60 00       	mov    $0x601030,%edi
  400557:	ff e2                	jmpq   *%rdx
  400559:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400560 <__do_global_dtors_aux>:
  400560:	80 3d c5 0a 20 00 00 	cmpb   $0x0,0x200ac5(%rip)        # 60102c <_edata>
  400567:	75 11                	jne    40057a <__do_global_dtors_aux+0x1a>
  400569:	55                   	push   %rbp
  40056a:	48 89 e5             	mov    %rsp,%rbp
  40056d:	e8 7e ff ff ff       	callq  4004f0 <deregister_tm_clones>
  400572:	5d                   	pop    %rbp
  400573:	c6 05 b2 0a 20 00 01 	movb   $0x1,0x200ab2(%rip)        # 60102c <_edata>
  40057a:	f3 c3                	repz retq 
  40057c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400580 <frame_dummy>:
  400580:	48 83 3d 68 08 20 00 	cmpq   $0x0,0x200868(%rip)        # 600df0 <__JCR_END__>
  400587:	00 
  400588:	74 1e                	je     4005a8 <frame_dummy+0x28>
  40058a:	b8 00 00 00 00       	mov    $0x0,%eax
  40058f:	48 85 c0             	test   %rax,%rax
  400592:	74 14                	je     4005a8 <frame_dummy+0x28>
  400594:	55                   	push   %rbp
  400595:	bf f0 0d 60 00       	mov    $0x600df0,%edi
  40059a:	48 89 e5             	mov    %rsp,%rbp
  40059d:	ff d0                	callq  *%rax
  40059f:	5d                   	pop    %rbp
  4005a0:	e9 7b ff ff ff       	jmpq   400520 <register_tm_clones>
  4005a5:	0f 1f 00             	nopl   (%rax)
  4005a8:	e9 73 ff ff ff       	jmpq   400520 <register_tm_clones>
  4005ad:	0f 1f 00             	nopl   (%rax)

00000000004005b0 <_Z16function_relaxedv>:
  4005b0:	55                   	push   %rbp
  4005b1:	48 89 e5             	mov    %rsp,%rbp
  4005b4:	be 00 00 00 00       	mov    $0x0,%esi
  4005b9:	bf 30 10 60 00       	mov    $0x601030,%edi
  4005be:	e8 8d 00 00 00       	callq  400650 <_ZNKSt13__atomic_baseIiE4loadESt12memory_order>
  4005c3:	5d                   	pop    %rbp
  4005c4:	c3                   	retq   

00000000004005c5 <main>:
  4005c5:	55                   	push   %rbp
  4005c6:	48 89 e5             	mov    %rsp,%rbp
  4005c9:	b8 00 00 00 00       	mov    $0x0,%eax
  4005ce:	5d                   	pop    %rbp
  4005cf:	c3                   	retq   

00000000004005d0 <_Z41__static_initialization_and_destruction_0ii>:
  4005d0:	55                   	push   %rbp
  4005d1:	48 89 e5             	mov    %rsp,%rbp
  4005d4:	48 83 ec 10          	sub    $0x10,%rsp
  4005d8:	89 7d fc             	mov    %edi,-0x4(%rbp)
  4005db:	89 75 f8             	mov    %esi,-0x8(%rbp)
  4005de:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
  4005e2:	75 1d                	jne    400601 <_Z41__static_initialization_and_destruction_0ii+0x31>
  4005e4:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
  4005eb:	75 14                	jne    400601 <_Z41__static_initialization_and_destruction_0ii+0x31>
  4005ed:	bf 30 10 60 00       	mov    $0x601030,%edi
  4005f2:	e8 3f 00 00 00       	callq  400636 <_ZNSt6atomicIiEC1Ev>
  4005f7:	bf 34 10 60 00       	mov    $0x601034,%edi
  4005fc:	e8 35 00 00 00       	callq  400636 <_ZNSt6atomicIiEC1Ev>
  400601:	c9                   	leaveq 
  400602:	c3                   	retq   

0000000000400603 <_GLOBAL__sub_I_x>:
  400603:	55                   	push   %rbp
  400604:	48 89 e5             	mov    %rsp,%rbp
  400607:	be ff ff 00 00       	mov    $0xffff,%esi
  40060c:	bf 01 00 00 00       	mov    $0x1,%edi
  400611:	e8 ba ff ff ff       	callq  4005d0 <_Z41__static_initialization_and_destruction_0ii>
  400616:	5d                   	pop    %rbp
  400617:	c3                   	retq   

0000000000400618 <_ZStanSt12memory_orderSt23__memory_order_modifier>:
  400618:	55                   	push   %rbp
  400619:	48 89 e5             	mov    %rsp,%rbp
  40061c:	89 7d fc             	mov    %edi,-0x4(%rbp)
  40061f:	89 75 f8             	mov    %esi,-0x8(%rbp)
  400622:	8b 55 fc             	mov    -0x4(%rbp),%edx
  400625:	8b 45 f8             	mov    -0x8(%rbp),%eax
  400628:	21 d0                	and    %edx,%eax
  40062a:	5d                   	pop    %rbp
  40062b:	c3                   	retq   

000000000040062c <_ZNSt13__atomic_baseIiEC1Ev>:
  40062c:	55                   	push   %rbp
  40062d:	48 89 e5             	mov    %rsp,%rbp
  400630:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  400634:	5d                   	pop    %rbp
  400635:	c3                   	retq   

0000000000400636 <_ZNSt6atomicIiEC1Ev>:
  400636:	55                   	push   %rbp
  400637:	48 89 e5             	mov    %rsp,%rbp
  40063a:	48 83 ec 10          	sub    $0x10,%rsp
  40063e:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  400642:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  400646:	48 89 c7             	mov    %rax,%rdi
  400649:	e8 de ff ff ff       	callq  40062c <_ZNSt13__atomic_baseIiEC1Ev>
  40064e:	c9                   	leaveq 
  40064f:	c3                   	retq   

0000000000400650 <_ZNKSt13__atomic_baseIiE4loadESt12memory_order>:
  400650:	55                   	push   %rbp
  400651:	48 89 e5             	mov    %rsp,%rbp
  400654:	48 83 ec 20          	sub    $0x20,%rsp
  400658:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  40065c:	89 75 e4             	mov    %esi,-0x1c(%rbp)
  40065f:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  400662:	be ff ff 00 00       	mov    $0xffff,%esi
  400667:	89 c7                	mov    %eax,%edi
  400669:	e8 aa ff ff ff       	callq  400618 <_ZStanSt12memory_orderSt23__memory_order_modifier>
  40066e:	89 45 fc             	mov    %eax,-0x4(%rbp)
  400671:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  400675:	8b 00                	mov    (%rax),%eax
  400677:	c9                   	leaveq 
  400678:	c3                   	retq   
  400679:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400680 <__libc_csu_init>:
  400680:	41 57                	push   %r15
  400682:	41 89 ff             	mov    %edi,%r15d
  400685:	41 56                	push   %r14
  400687:	49 89 f6             	mov    %rsi,%r14
  40068a:	41 55                	push   %r13
  40068c:	49 89 d5             	mov    %rdx,%r13
  40068f:	41 54                	push   %r12
  400691:	4c 8d 25 40 07 20 00 	lea    0x200740(%rip),%r12        # 600dd8 <__frame_dummy_init_array_entry>
  400698:	55                   	push   %rbp
  400699:	48 8d 2d 48 07 20 00 	lea    0x200748(%rip),%rbp        # 600de8 <__init_array_end>
  4006a0:	53                   	push   %rbx
  4006a1:	4c 29 e5             	sub    %r12,%rbp
  4006a4:	31 db                	xor    %ebx,%ebx
  4006a6:	48 c1 fd 03          	sar    $0x3,%rbp
  4006aa:	48 83 ec 08          	sub    $0x8,%rsp
  4006ae:	e8 b5 fd ff ff       	callq  400468 <_init>
  4006b3:	48 85 ed             	test   %rbp,%rbp
  4006b6:	74 1e                	je     4006d6 <__libc_csu_init+0x56>
  4006b8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4006bf:	00 
  4006c0:	4c 89 ea             	mov    %r13,%rdx
  4006c3:	4c 89 f6             	mov    %r14,%rsi
  4006c6:	44 89 ff             	mov    %r15d,%edi
  4006c9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  4006cd:	48 83 c3 01          	add    $0x1,%rbx
  4006d1:	48 39 eb             	cmp    %rbp,%rbx
  4006d4:	75 ea                	jne    4006c0 <__libc_csu_init+0x40>
  4006d6:	48 83 c4 08          	add    $0x8,%rsp
  4006da:	5b                   	pop    %rbx
  4006db:	5d                   	pop    %rbp
  4006dc:	41 5c                	pop    %r12
  4006de:	41 5d                	pop    %r13
  4006e0:	41 5e                	pop    %r14
  4006e2:	41 5f                	pop    %r15
  4006e4:	c3                   	retq   
  4006e5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  4006ec:	00 00 00 00 

00000000004006f0 <__libc_csu_fini>:
  4006f0:	f3 c3                	repz retq 
  4006f2:	66 90                	xchg   %ax,%ax

Disassembly of section .fini:

00000000004006f4 <_fini>:
  4006f4:	48 83 ec 08          	sub    $0x8,%rsp
  4006f8:	48 83 c4 08          	add    $0x8,%rsp
  4006fc:	c3                   	retq   
